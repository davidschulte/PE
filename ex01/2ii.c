// Exercise 2ii)
// David Schulte

#include <stdio.h>
#include <math.h>

int main()
{
	double x = 1;

	for(int i = 0; i < 3; i++)
		x = (x+2/x)/2;
	
	double error = fabs(x-sqrt(2));
	
	printf("Approximation of sqrt(2) by Babylonian method with 3 steps: %f\n", x);
	printf("Error: %f\n", error);

	return x;
}
