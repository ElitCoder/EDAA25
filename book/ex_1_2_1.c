#include <stdio.h>
#include <math.h>

int main(void)
{
    double  nbrs[] = {0, 0.1, 0.2, 0.3};
    int     i;
    
    for (i = 0; i < sizeof(nbrs) / sizeof(nbrs[0]); ++i)
        printf("sqrt(x): %.2f, e^x: %.2f\n", sqrt(nbrs[i]), exp(nbrs[i]));
        
    return 0;
}