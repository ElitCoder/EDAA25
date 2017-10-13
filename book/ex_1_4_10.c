#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N	(10000)

unsigned int* primes(size_t count)
{
	unsigned int*	primes = malloc(count * sizeof(unsigned int));
	int				i = 1, j;
	size_t			found = 0;
	bool			prime;
	
	if (primes == NULL)
		printf("malloc failed!\n");
	
	while (found < count) {
		prime = true;
		
		for (j = 2; j < i / 2; j++) {
			if (i % j == 0) {
				prime = false;
				
				break;
			}
		}
		
		if (prime)
			primes[found++] = i;
			
		i++;
	}
	
	return primes;
}

int main(void)
{
	unsigned int*	result = primes(N);
	int				i;
	
	for (i = 0; i < N; i++)
		printf("%u ", result[i]);
			
	printf("\n");
	
	free(result);
	
	return 0;
}