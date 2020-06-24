#include <string.h>

char* strncat(char *dest, const char *src, size_t len)
{
    strncpy(dest + strlen(dest), src, len);
    return dest;
}
