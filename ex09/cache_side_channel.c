/* cache_side_channel.c
 * Code inspired by CppCon18 talk on spectre from Chandler Carruth
*/

#include <x86intrin.h>
#include <stdio.h>

// our secret array
const char secret[] = "This is my secret!";
// just the size of our array
const int secret_size = sizeof(secret)/sizeof(char);

// read a memory location
void force_read(volatile __m128 *p) {
  // the volatile keyword prevents compiler/CPU optimizing the read away
  __m128 dummy = *p;
}

// high precision CPU timestamp
long read_timer()
{
  unsigned int dummy;
  return __rdtscp(&dummy);
}

// perform cache attack against data[idx]
char leak_byte(const char* data, int idx)
{
  // define array used to measure access times to cache lines
  // we use some larger stride larger than a cache line (64 bytes)
#define stride 512
  static __m128 timing_array[256*stride];
  // set the timing_array to some value so everything is well-defined
  // (and the physical memory is allocated, like needed for NUMA placement?)
  for(int i = 0; i < 256*stride; i++)
    timing_array[i] = _mm_setzero_ps();

  // array for measured latencies
  long latencies[256];
  for(int i = 0; i < 256; i++)
    latencies[i] = 0;

  for(int run = 0; run < 10; run++)
  {
    // flush all of timing array
    // (-> removes timing array from cache!)
    for(int i = 0; i < 256; i++)
      _mm_clflush(&timing_array[i * stride]);

    // perform reads that are data-dependent on the secret
    // as a program being attacked might
    for(int i = 0; i < 10; i++)
      force_read(&timing_array[data[idx] * stride]);

    // now measure read latencies to see if we can detect what data[idx] was
    for(int i = 0; i < 256; i++)
    {
      __m128 *timing_entry = &timing_array[i * stride];
      long start = read_timer();
      force_read(timing_entry);
      latencies[i] += read_timer() - start;
    }
  }

  // return the entry with the smallest measured latency
  char best_val = 0;
  for(int i = 0; i < 256; i++)
  {
    if( latencies[i] < latencies[best_val] )
      best_val = (char) i;
  }
  return best_val;
}


int main()
{
  for(int i = 0; i < secret_size; i++)
  {
    char c = leak_byte(secret, i);
    printf("got: %c\n", c);
  }
  return 0;
}

