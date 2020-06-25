#include <stdlib.h>

void *malloc(size_t size)
{
    return PhysM::malloc(size);
}

void free(void* ptr)
{
    return PhysM::free(ptr);
}
