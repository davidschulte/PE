#include <stdlib.h>
#include <stdio.h>


int main()
{

int n = 10;
int BLOCK = 2;


double* A = malloc(n*n*sizeof(double));
double* B = malloc(n*n*sizeof(double));
double* C = malloc(n*n*sizeof(double));
double* tmpA = malloc(n*n*sizeof(double));
double* tmpB = malloc(n*n*sizeof(double));
double* tmpC = malloc(n*n*sizeof(double));

double cij;


  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
      A[i+j*n] = ((double)j)+1.;
  }

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      B[i+j*n] =((double) i)*n+((double)j);



for(int i = 0; i < n; i += BLOCK)
{
	for(int j = 0; j < n; j += BLOCK)
	{
		for(int jc = 0; jc < BLOCK; jc++)
			for(int ic = 0; ic < BLOCK; ic++)
				tmpC[i+j*BLOCK] = 0;

		for(int k = 0; k < n; k += BLOCK)
		{
			for(int j_ = 0; j_ < BLOCK; j_++)
				for(int i_ = 0; i_ < BLOCK; i_++)
				{
					tmpA[i_+j_*BLOCK] = A[i+i_+(k+j_)*n];
					tmpB[i_+j_*BLOCK] = B[i+k+(j+j_)*n];
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
		for(int jc  = 0; jc < BLOCK; jc++)
			for(int ic = 0; ic < BLOCK; ic++)
				C[i+ic+(j+jc)*n] = tmpC[ic+jc*BLOCK];
	}					
}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf(" %g", C[i*n + j]);
		printf("\n");
	}


free(A);
free(B);
free(C);
free(tmpA);
free(tmpB);
free(tmpC);

return 0;
}
