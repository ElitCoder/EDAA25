#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "list.h"

#define N	(10000)

void test_list(void)
{
	list_t*	list = NULL;
	int		i;
	double	start, end;
	
	start = clock();
	
	for (i = 0; i < N; i++)
		insert_last(&list, &i);
		
	end = clock();
				
	free_list(&list);
	
	printf("time: %f\n", 
}

int main(void)
{
	test_list();
	
	return 0;
}