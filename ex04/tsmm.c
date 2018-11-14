#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sched.h>

int main()
{

int nb = 2;
int n = 10;

double M[2][2];
double *V = (double*) malloc(size(double) * n * nb);
double *W = (double*) malloc(size(double) * n * nb);

for(int i = 0; i < n; i++)
	for(int j = 0; i < nb; j++)
		V[i*n+j] = j+1;

for(int i = 0; i < nb; i++)
	for(int j = 0; j < nb; j++)
		M[i][j] = i*nb+j;

for(int i = 0; i < n; i++)
	for(int j = 0; j < nb; j++)
		W[i*n+j] = 0;

for(int i = 0; i < n; i++)
	for(int j = 0; j < nb; j++)
		for(int k = 0 ; k < nb; k++)
			W[i+n*j] = W[i+n*j] + V[i*n+k] * M[k][j];



return 0;
}
