#include <string.h>

void* memset(void* buf, int value, size_t size)
{
    uint8_t* bufptr = static_cast<uint8_t*>(buf);

    for(size_t i = 0; i < size; i++)
        bufptr[i] = (uint8_t)value;

    return buf;
}
