#include <stdio.h>

int putc(const char c)
{
    if (serial_debug)
         Serial::serial_putch(c);

    return TTY::tty_putc(c);
}
