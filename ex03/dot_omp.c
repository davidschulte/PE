#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sched.h>

int main()
{
	int threads;
	int core;
	int currentThread;
	double sum = 0;
	int n;

	printf("Please input n: ");
	scanf("%d", &n);	

	double* x = (double *) malloc(sizeof(double) * n);
	double* y = (double *) malloc(sizeof(double) * n);



	#pragma omp parallel
	{
		core = sched_getcpu();
		threads = omp_get_num_threads();
		currentThread = omp_get_thread_num();
		printf("Thread %d / %d on core %d\n", currentThread,
			threads, core);
	}



	#pragma omp parallel for schedule(static)
	for (int i = 0; i < n; i = i + 1)
	{
		x[i] = (double)1 / (double)(i+1);
		y[i] = (double)1 / (double)(i+2);
	}}



	double wtime = omp_get_wtime();

	#pragma omp parallel for schedule(static) reduction(+:sum)
	for(int i = 0; i < n; i++)
	{
		sum = sum + x[i] * y[i];
	}


	wtime = omp_get_wtime() - wtime;
	int flops = 2 * n;
	int bytes = 24 * n + 8;
	double GFps = (double) flops / wtime / 1000000.0;
	double GBps = (double) bytes / wtime / 1000000.0;
	double error = sum - 1.0  + 1.0  / (double) (n+1);


	printf("Result = %f\n", sum);
	printf("Time : %fs\n", wtime);
	printf("GigaFlops / s: %f\n", GFps);
	printf("GibaBytes / s: %f\n", GBps);
	printf("error = %f", error);



	free(x);
	free(y);

}
