#include <stdlib.h>

int itoa(int i, char* buf, size_t len)
{
    const char* digit = "0123456789";
    size_t index = 0;

    if(i < 0)
    {
        buf[index++] = '-';
        i *= -1;
    }

    int shifter = i;

    do
    {
        index++;
        shifter /= 10;
    }while(len > index && shifter);

    buf[index] = '\0';

    do
    {
        buf[--index] = digit[i % 10];
        i /= 10;
    }while(i);

    return 0;
}
