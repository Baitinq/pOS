#include <kernel/physm.h>

int PhysM::init(void)
{

    return 0;
}

void* PhysM::malloc(size_t size)
{
    if(!size)
        return NULL;

    return NULL;
}

void PhysM::free(void* ptr)
{
    if(!ptr)
        return;
}
