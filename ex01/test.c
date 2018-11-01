#include <stdio.h> 
#include <stdlib.h> 
  
int main() 
{ 
    int r = 3, c = 4, i, j, count; 
  
    double **arr = (double **)malloc(r * sizeof(double *)); 
    for (i=0; i<r; i++) 
         arr[i] = (double *)malloc(c * sizeof(double)); 
  
    // Note that arr[i][j] is same as *(*(arr+i)+j) 
    count = 0; 
    for (i = 0; i <  r; i++) 
      for (j = 0; j < c; j++) 
         arr[i][j] = ++count;  // OR *(*(arr+i)+j) = ++count 
  
    for (i = 0; i <  r; i++) 
      for (j = 0; j < c; j++) 
         printf("%f ", arr[i][j]); 
  
   /* Code for further processing and free the  
      dynamically allocated memory */
  
   return 0; 
} 

