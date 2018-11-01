// Exercise 1 Task 3
// David Schulte 6026591

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void printMatrix(int n, int m, double **a, char* name);
void multiplyMatrices(int n, int m, int k, double** a, double** b, double** c);
void initializeMatrices(int n, int m, int k, double** a, double** b);


int main()
{
	// Initializes and reads matrix dimensions
	int n,m,k;
	printf("Please enter n: ");
	scanf("%d", &n);
	printf("Please enter m: ");
	scanf("%d", &m);
	printf("Please enter k: ");
	scanf("%d", &k);

	// Initializes matrices with dynamic memory allocation
	double **a = (double **) malloc(sizeof(double *)*n);
	for(int i = 0; i < n; i++)
		a[i] = (double *) malloc(sizeof(double)*m);	

	double** b = (double **) malloc(sizeof(double *)*m);
	for(int i = 0; i < m; i++)
		b[i] = (double *) malloc(sizeof(double)*k);
	
	double** c = (double **) malloc(sizeof(double *)*n);
	for(int i = 0; i < n; i++)
		c[i] = (double *) malloc(sizeof(double)*k);

	
	// Assigns Values to matrices A and B
	initializeMatrices(n,m,k,a,b);

	// Matrix-multiplication and time measurement
	double wtime = omp_get_wtime();	
	multiplyMatrices(n,m,k,a,b,c);
	wtime = omp_get_wtime() - wtime;
	printf("Run time: %g\n", wtime);


	// Prints Matrices, if all dimensions are smaller than 5
	if(n < 5 && m < 5 && k < 5)
	{
		printMatrix(n,m,a,"A");
		printMatrix(m,k,b,"B");
		printMatrix(n,k,c,"C");
	}


	// The multiplication takes 3*n*m*k flops. This leads to a simple formula for the gigaFlops/s
	double gigaFlops = ((double) 3*n*m*k)/((double) 1000000000)/wtime;
	printf("Gigaflops/s: %f\n", gigaFlops);	

	// Frees memory
	free(a);
	free(b);
	free(c);

	return 0;
}



// Prints a matrix, given its dimensions and a name to display
void printMatrix(int n, int m, double **a, char* name)
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

// Assigns matrices A and B the values defined on the sheet
void initializeMatrices(int n, int m, int k, double** a, double** b)
{
	int min = n;
	if(m < n)
		min = m;

	for(int i = 0; i < min; i++)
		a[i][i] = 2;

	for(int i = 0; i < m-1; i++)
		a[i][i+1] = 1;

	for(int i = 0; i < n-1; i++)
		a[i+1][i] = 1;


	for(int i = 0; i < m; i++)
		for(int j = 0; j < k; j++)
			b[i][j] = ((double)j+1)/((double)i+1);
}	

// Multiplies two matrices given their dimensions
// Doesn't return the result but updates a result matrix, that has to pre-defined
void multiplyMatrices(int n, int m, int k, double **a, double **b, double **c)
{
	for(int i = 0; i < n; i++)
		for(int j = 0; j < k; j++)
			for(int l = 0; l < m; l++)
				c[i][j] += a[i][l]*b[l][j];
}
