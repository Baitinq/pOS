#include <kernel/debug.h>

static void debugger_out(char c)
{
     Serial::serial_putch(c);
}

static void debugger_putch(char*&, char c) //wrapper so that we can sprintf
{
    debugger_out(c);
}

int dbgprint(const char* str, int len)
{
    for (int i = 0; i < len; ++i)
        debugger_out(str[i]);
    return 0;
}

int dbgprintf(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int ret = printf_internal(debugger_putch, nullptr, fmt, ap);
    va_end(ap);
    return ret;
}
