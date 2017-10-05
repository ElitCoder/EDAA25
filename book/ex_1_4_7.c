#include <stdio.h>
#include <string.h>

#define SIZE (5)

double sum(double a[], size_t len)
{
	double	sum = 0;
	size_t	i;
	
	for (i = 0; i < len; i++)
		sum += a[i];
		
	return sum;
}

int main(void)
{
	double	a[SIZE] = {1, 2, 3, 4, 5};
	
	printf("sum: %f\n", sum(a, SIZE));
	
	return 0;
}