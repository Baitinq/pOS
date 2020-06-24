#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdarg.h>
#include <string.h>
#include <kernel/tty.h>
#include <printf_internal.h>
#include <kernel/serial.h>

#define EOF (-1)

int printf(const char* format, ...);
int sprintf(char* buf, const char* format, ...);
int print(const char* str);
int putc(const char c);

char getc(void); //for now void

class Debug
{
public:
    static void set_serial_debug(bool state);
};

#endif

