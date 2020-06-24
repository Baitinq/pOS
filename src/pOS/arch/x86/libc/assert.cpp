#include <assert.h>

void _assert(const char* expr, const char* file, int line)
{
    printf("Assertion failed! (%s) - %s:%d\n", expr, file ,line);
    /* TODO: Implement exit */
}
