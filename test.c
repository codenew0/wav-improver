#include "stdio.h"

static int x = 0;

int res(int n)
{
    x++;
    if (n <= 3)
        return n + 1;
    return res(n-4)+res(n-1);
}

int main()
{
    int n = 15;
    
    int r = res(n);
    
    printf("r: %d x: %d\n", r, x);
    
    return 0;
}
