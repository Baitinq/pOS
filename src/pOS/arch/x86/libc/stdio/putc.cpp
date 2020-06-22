#include <stdio.h>

int putc(const char c)
{
    return TTY::tty_putc(c);
}
