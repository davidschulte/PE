#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sched.h>
#include <emmintrin.h>

void printMatrix1D(double *a, char* name, int n, int m, int rows);
void printMatrix2D(int n, int m, double a[n][m], char* name);


int main()
{

int abortPrint = 0;
int abortParallelCheck = 0;

if(abortParallelCheck == 0)
{
#pragma omp parallel
{
	int all = omp_get_num_threads();
        int id = omp_get_thread_num();
       	// int coreID = sched_getcpu();
        printf("Thread %d / %d\n", id, all);
}
}



int nb = 4;
int n = 2000000/nb;
printf("Please enter n: ");
scanf("%d", &n);


double M[nb][nb];
double *V = NULL;
posix_memalign((void **)&V, 16, n*nb*sizeof(double));
// double *W = malloc(sizeof(double) * n * nb);
double *W = NULL;
posix_memalign((void **)&W, 16, n*nb*sizeof(double));


#pragma omp parallel for schedule(static)
for(int i = 0; i < n; i++)
	for(int j = 0; j < nb; j++)
		V[i*nb+j] = j+1;

for(int i = 0; i < nb; i++)
	for(int j = 0; j < nb; j++)
		M[i][j] = i*nb+j;


double wtime = omp_get_wtime();


#pragma omp parallel for schedule(static)
for(int i = 0; i < n; i++)
{
	W[i*2] = 0;
	W[i*2+1] = 0;
	__m128d vi1 = _mm_load_pd1(&V[i*2]); 			// load V_i1 into both SSE elements
	__m128d m1 = _mm_set_pd(M[0][1],M[0][0]); 		// set first row of M
	__m128d vi1m1 = _mm_mul_pd(vi1,m1); 			// multiply V_i1 with row of M
	__m128d vi2 = _mm_load_pd1(&V[i*2+1]); 			// load V(i,2) into both SSE elements
	__m128d m2 = _mm_set_pd(M[1][1],M[1][0]); 		// set second row of M
	__m128d vi2m2 = _mm_mul_pd(vi2,m2); 			// multiply V_i2 with row of M
	__m128d wi = _mm_add_pd(vi1m1,vi2m2); 			// add up row of W
	_mm_stream_pd(&W[i*2], wi); 				// write result to W using non-temporal store
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
