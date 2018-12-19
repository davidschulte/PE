#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <mkl.h>
#define BLOCK 16

void printMatrix(double *A, int n, int m, char name, int stride);
void recursivegemm(const int n, const int stride, const double *restrict A, const double *restrict B, double *restrict C);

int main()
{

	int printMax = 32;
	int n;
	printf("Please input n: ");
	scanf("%d", &n);
	
	int stride = n + 20;

	double alpha = 1;
	double beta = 0;

	
        double *A = malloc(n*stride*sizeof(double));
        double *B = malloc(n*stride*sizeof(double));
        double *C = malloc(n*stride*sizeof(double));

	for(int j = 0; j < n; j++)
		for(int i = 0; i < n; i++)
		{
			A[i+j*stride] = (i==j) ? 2 : 1;
			B[i+j*stride] = j*1./n;
			C[i+j*stride] = 0;
		}


	double time = omp_get_wtime();
	dgemm("N","N",&n,&n,&n,&alpha,A,&stride,B,&stride,&beta,C,&stride);
	time = omp_get_wtime() - time;

	if(n <= printMax)
	{
		printMatrix(A,n,n,'A',stride);
		printMatrix(B,n,n,'B',stride);
		printMatrix(C,n,n,'C',stride);
	}


	printf("n = %d\n", n);
	double gigaFlops = ((double) n*n*n)/(time * 1000000000.0);
	printf("Runtime:\t%fs\nPerformance:\t%f Gigaflops/s\n", time, gigaFlops);

	free(A);
	free(B);
	free(C);

}

void printMatrix(double *A, int n, int m, char name, int stride)
{
	printf("%c\n", name);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
			printf("%f\t", A[i+j*stride]);
		printf("\n");
	}
}
