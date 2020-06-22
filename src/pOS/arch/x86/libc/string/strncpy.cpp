#include <string.h>

char* strncpy(char* dst, const char* src, size_t len)
{
    if(!dst)
        return NULL;
    char* dstptr = dst;

    while(*src && len--)
        *dst++ = *src++;
    *dst = '\0';

    return dstptr;
}
