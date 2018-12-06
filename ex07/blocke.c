
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>
#include <sched.h>

int main(){
    int n=10;
    double A [n*n];
    double B [n*n];
    double C[n*n];
int BLOCK=5;
double tmpA[BLOCK*BLOCK];
double tmpB[BLOCK*BLOCK];
double tmpC[BLOCK*BLOCK];

  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
      A[i*n+j] = ((double)j)+1.;
  }

 for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
      C[i*n+j] =((double)0);
  }
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      B[i*n+j] =((double) i)*n+((double)j);

 // if( n < 10 )
 // {
    printf("A:\n");
    for(int i = 0; i < n; i++)
    {
       for(int j = 0; j < n; j++)
         printf(" %g", A[i*n+j]);
       printf("\n");
    }
    printf("B:\n");
    for(int i = 0; i < n; i++)
    {
       for(int j = 0; j < n; j++)
         printf(" %g", B[i*n+j]);
       printf("\n");
    }
 // }
for ( int i = 0 ; i < n ; i+=BLOCK)
{
	for ( int j = 0 ; j < n ; j+=BLOCK)
	{
		double cij = 0 ;
		for ( int k = 0 ; k < n ; k+=BLOCK){

			for ( int k_ = 0 ; k_ < BLOCK; k_++)
				for ( int i_ = 0 ; i_ < BLOCK; i_++)
					tmpA[ i_+k_*BLOCK] = A[ i+i_ + ( k+k_)*n ] ;

			for ( int j_ = 0 ; j_ < BLOCK; j_++)
				for ( int k_ = 0 ; k_ < BLOCK; k_++)
					tmpB[k_+j_*BLOCK] = B[ k+k_ + ( j+j_)*n ] ;

			for ( int j_ = 0 ; j_ < BLOCK; j_++)
				for ( int i_ = 0 ; i_ < BLOCK; i_++)
					tmpC[ i_+j_ *BLOCK ]=0;

			for ( int i_ = 0 ; i_ < BLOCK; i_++){
				for ( int j_ = 0 ; j_ < BLOCK; j_++){
					for ( int k_ = 0 ; k_ < BLOCK; k_++){
						cij += tmpA[ i_+k_*BLOCK ] * tmpB[ k_+j_ *BLOCK ] ;
						tmpC[ i_+j_ *BLOCK ] = cij ;
					}
				}
			}

			for ( int j_ = 0 ; j_ < BLOCK; j_++)
				for ( int i_ = 0 ; i_ < BLOCK; i_++)
					C[i+i_ + ( j+j_)*n ]=tmpC[ i_+j_ *BLOCK ];
		}
	}
}
 printf("C:\n");
    for(int i = 0; i < n; i++)
    {
       for(int j = 0; j < n; j++)
         printf(" %g", C[i*n+j]);
       printf("\n");
    }
  return 0;
}
