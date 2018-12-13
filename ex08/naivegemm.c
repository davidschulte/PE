#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#define BLOCK 8

void printMatrix(double *A, int n, int m, char name, int stride);
double* gemmEx1(double *A, double *B, int n, int m, int o, int stide);
double* gemmUAJ(double* A, double* B, int n, int roll);
double* gemmBlock(double* A, double* B, int n);

int main(){

	int printMax = 32;
	int n;
	printf("Please input n: ");
	scanf("%d", &n);
	
	int stride = n + 20;
	
        double *A = malloc(n*stride*sizeof(double));
        double *B = malloc(n*stride*sizeof(double));

	for(int j = 0; j < n; j++)
		for(int i = 0; i < n; i++)
			A[i+j*stride] = (i==j) ? 2 : 1;


        for(int j = 0; j < n; j++)
                for(int i = 0; i < n; i++)
                        B[i+j*stride] = j*1./n;


	double time = omp_get_wtime();
	double*	C = gemmEx1(A,B,n,n,n,stride);
	time = omp_get_wtime() - time;

	if(n < printMax)
	{
		printMatrix(A,n,n,'A',stride);
		printMatrix(B,n,n,'B',stride);
		printMatrix(C,n,n,'C',stride);
	}

	printf("Naive:\t%fs\n", time);

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


double* gemmEx1(double *A, double *B, int n, int m, int o, int stride)
{
	double *C = malloc(n*stride*sizeof(double));
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < o; j++)
		{
			C[i+j*stride] = 0;
			for(int k = 0; k < m; k++)
				C[i+j*stride] += A[i+k*stride] * B[k+j*stride];
		}

	return C;
}

double* gemmUAJ(double* A, double* B, int n, int roll)
{
	double *C = malloc(n*n*sizeof(double));
	double *cij = malloc(roll*sizeof(double));

	int i = 0;
	while(i < n - roll)
	{
		for(int j = 0; j < n; j++)
		{
			for (int l = 0; l < roll; l++)
				cij[l] = 0;
			for(int k = 0; k < n; k++)
				for(int l = 0; l < roll; l++)
					cij[l] += A[i+l+k*n] * B[k+j*n];
			for(int l = 0; l < roll; l++)
			{
				C[i+l+j*n]  = cij[l];
				printf("%f\t", cij[l]);
			}
	 	}
		i += roll;
	}

	int rest =  n - i;
	for(int j = 0; j < n; j++)
	{
		for (int l = 0; l < rest; l++)
			cij[l] = 0;
		for(int k = 0; k < n; k++)
			for(int l = 0; l < rest; l++)
				cij[l] += A[i+l+ k*n] * B[k+j*n];
		for(int l = 0; l < rest; l++)
			C[i+l+j*n] = cij[l];
	}

	free(cij);
	return C;
}

double* gemmBlock(double *A, double* B, int n)
{

	double* C = malloc(n*n*sizeof(double));
	double* tmpA = malloc(n*n*sizeof(double));
	double* tmpB = malloc(n*n*sizeof(double));
	double* tmpC = malloc(n*n*sizeof(double));

	double cij;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			A[i+j*n] = ((double)j)+1.; for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
		B[i+j*n] =((double) i)*n+((double)j);
	for(int i = 0; i < n; i += BLOCK)
	{
		for(int j = 0; j < n; j += BLOCK)
		{
			for(int jc = 0; jc < BLOCK; jc++)
				for(int ic = 0; ic < BLOCK; ic++)
					tmpC[ic+jc*BLOCK] = 0;
			for(int k = 0; k < n; k += BLOCK)
			{
				for(int j_ = 0; j_ < BLOCK; j_++)
					for(int i_ = 0; i_ < BLOCK; i_++)
					{
						tmpA[i_+j_*BLOCK] = A[i_+i+(k+j_)*n];
						tmpB[i_+j_*BLOCK] = B[i_+k+(j+j_)*n];
					}
				for(int jb = 0; jb < BLOCK; jb++)
					for(int ib = 0; ib < BLOCK; ib++)
					{
						cij = 0;
						for(int kb = 0; kb < BLOCK; kb++)
							cij += tmpA[ib+kb*BLOCK]*tmpB[kb+jb*BLOCK];
						tmpC[ib+jb*BLOCK] += cij;
					}
			}
			for(int jc = 0; jc < BLOCK; jc++)
				for(int ic = 0; ic < BLOCK; ic++)
					C[i+ic+(j+jc)*n] = tmpC[ic+jc*BLOCK];
		}
	}
	free(tmpA);
	free(tmpB);
	free(tmpC);
					
	return C;
}
