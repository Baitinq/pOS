#include <stdio.h>

static bool serial_debug = false;

void Debug::set_serial_debug(bool state)
{
    serial_debug = state;
}

static void console_out(char c)
{
   if (serial_debug)
        Serial::serial_putch(c);

    putc(c);
}

static void console_putch(char*&, char c) //wrapper so that we can sprintf
{
    console_out(c);
}

int printf(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int result = printf_internal(console_putch, nullptr, fmt, ap);
    va_end(ap);
    return result;
}

int print(const char* str, int len)
{
    for (int i = 0; i < len; ++i)
        console_out(str[i]);
    return 0;
}
