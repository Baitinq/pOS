#include <string.h>

int strncmp(const char* str1, const char* str2, size_t len)
{
    size_t strln = strlen(str1);
    strln = strln > strlen(str2) ? strlen(str2) : strln;
    strln = strln > len ? len : strln;
    return memcmp(str1, str2, strln);
}
