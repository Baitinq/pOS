#ifndef _ASSERT_H_
#define _ASSERT_H_

#include <stdio.h>

#define ASSERT(EXPR) (void)((EXPR) || (_assert (#EXPR, __FILE__, __LINE__),0))

static inline void _assert(const char* expr, const char* file, int line)
{
    printf("Assertion failed! (%s) - %s:%d\n", expr, file ,line);
    /* TODO: Implement exit */
}

#endif
