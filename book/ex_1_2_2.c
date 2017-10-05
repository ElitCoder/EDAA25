#include <stdio.h>

int main(void)
{
    printf("unsigned short: %lu bytes\n", sizeof(unsigned short));
    printf("unsigned int: %lu bytes\n", sizeof(unsigned int));
    printf("unsigned long: %lu bytes\n", sizeof(unsigned long));
    printf("unsigned long long: %lu bytes\n", sizeof(unsigned long long));
    
    return 0;
}