#include <stdio.h>
#include <time.h>

int main(void)
{
    double	sum = 0;
	int		i;
	clock_t	start, end;
	
	start = clock();
    
    for (i = 1; sum <= 18; ++i)
		sum += 1 / (double)i;
		
	end = clock();
	
	printf("terms: %d\n", i);
	printf("sum: %f\n", sum);
	printf("time: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    return 0;
}