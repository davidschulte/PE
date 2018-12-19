#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

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
	recursivegemm(n, stride, A, B, C);
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


void recursivegemm(const int n, const int stride, const double *restrict A, const double *restrict B, double *restrict C)
{
	if(n > BLOCK)
	{
		const int h = n / 2;

		recursivegemm(h, stride, &A[0+0*stride], &B[0+0*stride], &C[0+0*stride]);
		recursivegemm(h, stride, &A[0+h*stride], &B[h+0*stride], &C[0+0*stride]);

                recursivegemm(h, stride, &A[h+0*stride], &B[0+0*stride], &C[h+0*stride]);
                recursivegemm(h, stride, &A[h+h*stride], &B[h+0*stride], &C[h+0*stride]);

                recursivegemm(h, stride, &A[0+h*stride], &B[h+h*stride], &C[0+h*stride]);
                recursivegemm(h, stride, &A[0+0*stride], &B[0+h*stride], &C[0+h*stride]);

                recursivegemm(h, stride, &A[h+h*stride], &B[h+h*stride], &C[h+h*stride]);
                recursivegemm(h, stride, &A[h+0*stride], &B[0+h*stride], &C[h+h*stride]);

		return;
	}


	double* tmpA = malloc(BLOCK*BLOCK*sizeof(double));
        double* tmpB = malloc(BLOCK*BLOCK*sizeof(double));
        double* tmpC = malloc(BLOCK*BLOCK*sizeof(double));
	double cij;

	for(int j = 0; j < BLOCK; j++)
		for(int i = 0; i < BLOCK; i++)
		{
			tmpA[i+j*BLOCK] = A[i+j*stride];
			tmpB[i+j*BLOCK] = B[i+j*stride];
		}

        for(int j = 0; j < BLOCK; j++)
                for(int i = 0; i < BLOCK; i++)
                {
                	cij = 0;
			for(int k = 0; k < BLOCK; k++)
				cij += tmpA[i+k*BLOCK] * tmpB[k+j*BLOCK];
			tmpC[i+j*BLOCK] = cij;
                }

        for(int j = 0; j < BLOCK; j++)
                for(int i = 0; i < BLOCK; i++)
                {
                        C[i+j*stride] += tmpC[i+j*BLOCK];
                }

	free(tmpA);
	free(tmpB);
	free(tmpC);
}
