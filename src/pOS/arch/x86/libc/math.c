#include <math.h>

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int pow(int num, int p)
{
    int result = 1;
    for(int i = 0; i < p; i++)
    {
        result *= num;
    }

    return result;
}
