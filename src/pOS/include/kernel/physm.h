#ifndef _PHYSM_H_
#define _PHYSM_H_

#include <stddef.h>

class PhysM
{
public:
    static int init(void);
    static void *malloc(size_t size);
    static void free(void* ptr);
};

#endif
