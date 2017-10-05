#include <stdio.h>

#define SIZE (5)

void input(double a[], size_t size)
{
	size_t	i;
	
	for (i = 0; i < size; i++)
		if (scanf("%lf", &a[i]) != 1)
			printf("scanf wrong return value\n");
}

int main(void)
{
	double	a[SIZE];
	int		i;
	
	input(a, SIZE);

	for (i = 0; i < SIZE; i++)
		printf("%f ", a[i]);
		
	printf("\n");
	
	return 0;
}