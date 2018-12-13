#include <stdio.h>

#include <math.h>
#include <stdlib.h>
#include <omp.h>

void printMatrix(double *A, int n, int m, char name, int stride);
double* gemmEx1(double *A, double *B, int n, int m, int o, int stide);

int main(){

	int printMax = 32;
	int n;
	printf("Please input n: ");
	scanf("%d", &n);
	
	int stride = n;
	
        double *A = malloc(n*stride*sizeof(double));
        double *B = malloc(n*stride*sizeof(double));
	double *C = malloc(n*n*sizeof(double));

	for(int j = 0; j < n; j++)
		for(int i = 0; i < n; i++)
			A[i+j*stride] = (i==j) ? 2 : 1;


        for(int j = 0; j < n; j++)
                for(int i = 0; i < n; i++)
                        B[i+j*stride] = j*1./n;

	int roll = 8;
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

	if(n < printMax)
	{
		printMatrix(A,n,n,'A',stride);
		printMatrix(B,n,n,'B',stride);
		printMatrix(C,n,n,'C',stride);
	}

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

