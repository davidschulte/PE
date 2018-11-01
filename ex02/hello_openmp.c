#define _GNU_SOURCE
#include <stdio.h>
#include <omp.h>
#include <sched.h>

int main()
{
	
	#pragma omp parallel
	{
		int all = omp_get_num_threads();
		int id = omp_get_thread_num();
		int coreID = sched_getcpu();
		printf("Thread %d / %d from core %d", id, all, coreID);
	}
}
