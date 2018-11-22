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



int nb = 8;
int n;
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

// nb = 8
#pragma omp parallel for schedule(static)
for(int i = 0; i < n; i++)
{
	for(int j = 0; j < nb; j++)
		W[i*nb+j] = 0;

	__m128d vi1 = _mm_load_pd1(&V[i*nb]);
	__m128d m1_1 = _mm_set_pd(M[0][1],M[0][0]);
	__m128d m1_2 = _mm_set_pd(M[0][3],M[0][2]);
        __m128d m1_3 = _mm_set_pd(M[0][5],M[0][4]);
        __m128d m1_4 = _mm_set_pd(M[0][7],M[0][6]);
	__m128d vi1m1_1 = _mm_mul_pd(vi1,m1_1);
	__m128d vi1m1_2 = _mm_mul_pd(vi1,m1_2);
        __m128d vi1m1_3 = _mm_mul_pd(vi1,m1_3);
        __m128d vi1m1_4 = _mm_mul_pd(vi1,m1_4);


	__m128d vi2 = _mm_load_pd1(&V[i*nb+1]);
        __m128d m2_1 = _mm_set_pd(M[1][1],M[1][0]);
        __m128d m2_2 = _mm_set_pd(M[1][3],M[1][2]);
        __m128d m2_3 = _mm_set_pd(M[1][5],M[1][4]);
        __m128d m2_4 = _mm_set_pd(M[1][7],M[1][6]);
        __m128d vi2m2_1 = _mm_mul_pd(vi2,m2_1);
        __m128d vi2m2_2 = _mm_mul_pd(vi2,m2_2);
        __m128d vi2m2_3 = _mm_mul_pd(vi2,m2_3);
        __m128d vi2m2_4 = _mm_mul_pd(vi2,m2_4);

        __m128d vi3 = _mm_load_pd1(&V[i*nb+2]);
        __m128d m3_1 = _mm_set_pd(M[2][1],M[2][0]);
        __m128d m3_2 = _mm_set_pd(M[2][3],M[2][2]);
        __m128d m3_3 = _mm_set_pd(M[2][5],M[2][4]);
        __m128d m3_4 = _mm_set_pd(M[2][7],M[2][6]);
        __m128d vi3m3_1 = _mm_mul_pd(vi3,m3_1);
        __m128d vi3m3_2 = _mm_mul_pd(vi3,m3_2);
        __m128d vi3m3_3 = _mm_mul_pd(vi3,m3_3);
        __m128d vi3m3_4 = _mm_mul_pd(vi3,m3_4);

        __m128d vi4 = _mm_load_pd1(&V[i*nb+3]);
        __m128d m4_1 = _mm_set_pd(M[3][1],M[3][0]);
        __m128d m4_2 = _mm_set_pd(M[3][3],M[3][2]);
        __m128d m4_3 = _mm_set_pd(M[3][5],M[3][4]);
        __m128d m4_4 = _mm_set_pd(M[3][7],M[3][6]);
        __m128d vi4m4_1 = _mm_mul_pd(vi4,m4_1);
        __m128d vi4m4_2 = _mm_mul_pd(vi4,m4_2);
        __m128d vi4m4_3 = _mm_mul_pd(vi4,m4_3);
        __m128d vi4m4_4 = _mm_mul_pd(vi4,m4_4);
       
        __m128d vi5 = _mm_load_pd1(&V[i*nb+4]);
        __m128d m5_1 = _mm_set_pd(M[4][1],M[4][0]);
        __m128d m5_2 = _mm_set_pd(M[4][3],M[4][2]);
        __m128d m5_3 = _mm_set_pd(M[4][5],M[4][4]);
        __m128d m5_4 = _mm_set_pd(M[4][7],M[4][6]);
        __m128d vi5m5_1 = _mm_mul_pd(vi5,m5_1);
        __m128d vi5m5_2 = _mm_mul_pd(vi5,m5_2);
        __m128d vi5m5_3 = _mm_mul_pd(vi5,m5_3);
        __m128d vi5m5_4 = _mm_mul_pd(vi5,m5_4);


        __m128d vi6 = _mm_load_pd1(&V[i*nb+5]);
        __m128d m6_1 = _mm_set_pd(M[5][1],M[5][0]);
        __m128d m6_2 = _mm_set_pd(M[5][3],M[5][2]);
        __m128d m6_3 = _mm_set_pd(M[5][5],M[5][4]);
        __m128d m6_4 = _mm_set_pd(M[5][7],M[5][6]);
        __m128d vi6m6_1 = _mm_mul_pd(vi6,m6_1);
        __m128d vi6m6_2 = _mm_mul_pd(vi6,m6_2);
        __m128d vi6m6_3 = _mm_mul_pd(vi6,m6_3);
        __m128d vi6m6_4 = _mm_mul_pd(vi6,m6_4);

        __m128d vi7 = _mm_load_pd1(&V[i*nb+6]);
        __m128d m7_1 = _mm_set_pd(M[6][1],M[6][0]);
        __m128d m7_2 = _mm_set_pd(M[6][3],M[6][2]);
        __m128d m7_3 = _mm_set_pd(M[6][5],M[6][4]);
        __m128d m7_4 = _mm_set_pd(M[6][7],M[6][6]);
        __m128d vi7m7_1 = _mm_mul_pd(vi7,m7_1);
        __m128d vi7m7_2 = _mm_mul_pd(vi7,m7_2);
        __m128d vi7m7_3 = _mm_mul_pd(vi7,m7_3);
        __m128d vi7m7_4 = _mm_mul_pd(vi7,m7_4);

        __m128d vi8 = _mm_load_pd1(&V[i*nb+7]);
        __m128d m8_1 = _mm_set_pd(M[7][1],M[7][0]);
        __m128d m8_2 = _mm_set_pd(M[7][3],M[7][2]);
        __m128d m8_3 = _mm_set_pd(M[7][5],M[7][4]);
        __m128d m8_4 = _mm_set_pd(M[7][7],M[7][6]);
        __m128d vi8m8_1 = _mm_mul_pd(vi8,m8_1);
        __m128d vi8m8_2 = _mm_mul_pd(vi8,m8_2);
        __m128d vi8m8_3 = _mm_mul_pd(vi8,m8_3);
        __m128d vi8m8_4 = _mm_mul_pd(vi8,m8_4);


	__m128d wi_1_p1_1 = _mm_add_pd(vi1m1_1,vi2m2_1);
	__m128d wi_1_p1_2 = _mm_add_pd(vi3m3_1,vi4m4_1);
        __m128d wi_1_p2_1 = _mm_add_pd(vi5m5_1,vi6m6_1);
        __m128d wi_1_p2_2 = _mm_add_pd(vi7m7_1,vi8m8_1);
        __m128d wi_1_p1 = _mm_add_pd(wi_1_p1_1, wi_1_p1_2);
        __m128d wi_1_p2 = _mm_add_pd(wi_1_p2_1, wi_1_p2_2);
	__m128d wi_1 = _mm_add_pd(wi_1_p1, wi_1_p2);
	_mm_stream_pd(&W[i*nb], wi_1);

        __m128d wi_2_p1_1 = _mm_add_pd(vi1m1_2,vi2m2_2);
        __m128d wi_2_p1_2 = _mm_add_pd(vi3m3_2,vi4m4_2);
        __m128d wi_2_p2_1 = _mm_add_pd(vi5m5_2,vi6m6_2);
        __m128d wi_2_p2_2 = _mm_add_pd(vi7m7_2,vi8m8_2);
        __m128d wi_2_p1 = _mm_add_pd(wi_2_p1_1, wi_2_p1_2);
        __m128d wi_2_p2 = _mm_add_pd(wi_2_p2_1, wi_2_p2_2);
        __m128d wi_2 = _mm_add_pd(wi_2_p1, wi_2_p2);
        _mm_stream_pd(&W[i*nb+2], wi_2);

        __m128d wi_3_p1_1 = _mm_add_pd(vi1m1_3,vi2m2_3);
        __m128d wi_3_p1_2 = _mm_add_pd(vi3m3_3,vi4m4_3);
        __m128d wi_3_p2_1 = _mm_add_pd(vi5m5_3,vi6m6_3);
        __m128d wi_3_p2_2 = _mm_add_pd(vi7m7_3,vi8m8_3);
        __m128d wi_3_p1 = _mm_add_pd(wi_3_p1_1, wi_3_p1_2);
        __m128d wi_3_p2 = _mm_add_pd(wi_3_p2_1, wi_3_p2_2);
        __m128d wi_3 = _mm_add_pd(wi_3_p1, wi_3_p2);
        _mm_stream_pd(&W[i*nb+4], wi_3);
	
	__m128d wi_4_p1_1 = _mm_add_pd(vi1m1_4,vi2m2_4);
        __m128d wi_4_p1_2 = _mm_add_pd(vi3m3_4,vi4m4_4);
        __m128d wi_4_p2_1 = _mm_add_pd(vi5m5_4,vi6m6_4);
        __m128d wi_4_p2_2 = _mm_add_pd(vi7m7_4,vi8m8_4);
        __m128d wi_4_p1 = _mm_add_pd(wi_4_p1_1, wi_4_p1_2);
        __m128d wi_4_p2 = _mm_add_pd(wi_4_p2_1, wi_4_p2_2);
        __m128d wi_4 = _mm_add_pd(wi_4_p1, wi_4_p2);
        _mm_stream_pd(&W[i*nb+6], wi_4);
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
