#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

int main()
{

	double* a = malloc(5*sizeof(double));

	for(int i = 0; i < 5; i++)
	{
		a[i] = i;
		printf("%f\t", a[i]);
		printf("%x\n", &a[i]-i);
	}

	double *pTest = &a[2];
	printf("%f", pTest[1]);

	return 0;
}
