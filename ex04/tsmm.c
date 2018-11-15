#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sched.h>


void printMatrix1D(double *a, char* name, int n, int m, int rows);

int main()
{

int nb = 2;
int n = 4;

double M[nb][nb];
double *V = malloc(sizeof(double) * n * nb);
double *W = malloc(sizeof(double) * n * nb);

for(int i = 0; i < n; i++)
	for(int j = 0; j < nb; j++)
		V[i*nb+j] = j+1;

for(int i = 0; i < nb; i++)
	for(int j = 0; j < nb; j++)
		M[i][j] = i*nb+j;

for(int i = 0; i < n; i++)
	for(int j = 0; j < nb; j++)
		{
                W[i*nb+j] = 0;
		for(int k = 0 ; k < nb; k++)
			W[i*nb+j] = W[i*nb+j] + V[i*nb+k] * M[k][j];
		}

printMatrix1D(V, "V", n, nb, 1);
printMatrix1D(W, "W", n, nb, 1);


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
