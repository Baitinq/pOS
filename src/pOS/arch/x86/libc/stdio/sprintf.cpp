#include <stdio.h>

static void buffer_putch(char*& bufptr, char c)
{
    *bufptr++ = c;
}

int sprintf(char* buf, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int result = printf_internal(buffer_putch, buf, fmt, ap);
    buf[result] = '\0';
    va_end(ap);
    return result;
}
