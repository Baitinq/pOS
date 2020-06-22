#include <stdlib.h>

static int to_int(char c)
{
    return c - '0';
}

static bool is_num(char c)
{
    return (c >= '0' && c <= '9');
}

int atoi(const char* str)
{
    int result = 0;
    int index = 0;

    if(str[0] == '-')
        index++;

    while(str[index] != '\0')
    {
        ASSERT(is_num(str[index]));
        result = (to_int(str[index]) + (10 * result));
        index++;
    }

    if(str[0] == '-')
    {
        result *= -1;
    }

    return result;
}
