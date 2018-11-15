#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sched.h>


void printMatrix1D(double *a, char* name, int n, int m, int rows);
void printMatrix2D(int n, int m, double a[n][m], char* name);


int main()
{

int abortPrint = 1;
int abortParallelCheck = 0;

if(abortParallelCheck == 0)
{
#pragma omp parallel
{
	int all = omp_get_num_threads();
        int id = omp_get_thread_num();
        int coreID = sched_getcpu();
        printf("Thread %d / %d from core %d\n", id, all, coreID);
}
}



int nb = 8;
int n = 10000000;
scanf("%d", &n);


double M[nb][nb];
double *V = malloc(sizeof(double) * n * nb);
double *W = malloc(sizeof(double) * n * nb);


#pragma omp parallel for schedule(static)
for(int i = 0; i < n; i++)
	for(int j = 0; j < nb; j++)
		V[i*nb+j] = j+1;

for(int i = 0; i < nb; i++)
	for(int j = 0; j < nb; j++)
		M[i][j] = i*nb+j;

const int nIter = 100;

double wtime = omp_get_wtime();

for(int l = 0; l < nIter; l++)
	#pragma omp parallel for schedule(static) firstprivate(M)
	for(int i = 0; i < n; i++)
		for(int j = 0; j < nb; j++)
			{
                	W[i*nb+j] = 0;
			for(int k = 0 ; k < nb; k++)
				W[i*nb+j] = W[i*nb+j] + V[i*nb+k] * M[k][j];
			}

wtime = omp_get_wtime() - wtime;

double flops = 2.0*n*nb*nb;
double bytes = 8.0*(n*nb)*(1+4.0*nb);
double GFperS = flops / wtime / 1000000000.0;
double GBperS = bytes / wtime / 1000000000.0;


printf("Time : %f\n", wtime);
printf("GigaFlops/s: %f\n", GFperS);
printf("Gigabytes/s: %f\n", GBperS);


if(abortPrint == 0 && n < 10)
{
printMatrix1D(V, "V", n, nb, 1);
printMatrix2D(nb, nb, M, "M");
printMatrix1D(W, "W", n, nb, 1);
}

free(V);
free(W);

return 0;
}


void printMatrix1D(double *a, char* name, int n, int m, int rows)
{
        printf("Matrix %s:\n", name);
	if(rows == 1)
	{
        	for(int i = 0; i < n; i++)
                {
                	for(int j = 0; j < m; j++)
                        	printf("%f\t", a[i*m+j]);
                	printf("\n");
                }
        	printf("\n\n");
	}
	else
	{
                for(int i = 0; i < n; i++)
                {
                        for(int j = 0; j < m; j++)
                                printf("%f\t", a[i+j*n]);
                        printf("\n");
                }
                printf("\n\n");
        }

}

void printMatrix2D(int n, int m, double a[n][m], char* name)
{
        printf("Matrix %s:\n", name);
        for(int i = 0; i < n; i++)
                {
                for(int j = 0; j < m; j++)
                        printf("%f\t", a[i][j]);
                printf("\n");
                }
        printf("\n\n");
}

