#ifndef _ASSERT_H_
#define _ASSERT_H_

#include <stdio.h>

#define ASSERT(EXPR) (void)((EXPR) || (_assert (#EXPR, __FILE__, __LINE__),0))

extern "C" void _assert (const char *msg, const char *file, int line);

#endif
