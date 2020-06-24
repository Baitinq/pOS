#include <string.h>

int memcmp(const void* ptr1, const void* ptr2, size_t size)
{
    int result = 0;
    const uint8_t* p1 = static_cast<const uint8_t*>(ptr1);
    const uint8_t* p2 = static_cast<const uint8_t*>(ptr2);

    for(size_t i = 0; i < size; i++)
        if(*p1++ != *p2++)
            return *--p1 - *--p2;

    return result;
}
