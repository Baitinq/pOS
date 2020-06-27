#include <stdlib.h>

void *malloc(size_t size)
{
    return PhysM::malloc(size, false);
}

void *calloc(size_t size)
{
    return PhysM::malloc(size, true);
}

void* realloc(void* ptr, size_t size)
{
    return PhysM::realloc(ptr, size);
}

void free(void* ptr)
{
    return PhysM::free(ptr);
}
