#include <string.h>

void* memcpy(void* dst, const void* src, size_t size)
{
    uint8_t* dstptr = static_cast<uint8_t*>(dst);
    const uint8_t* srcptr = static_cast<const uint8_t*>(src);
    for (size_t i = 0; i < size; i++)
        dstptr[i] = srcptr[i];
    return dst;
}
