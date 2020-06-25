#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdarg.h>
#include <string.h>
#include <kernel/tty.h>
#include <printf_internal.h>
#include <kernel/serial.h>
#include "../../arch/x86/kernel/drivers/keyboard/include/kbbuf.h"

#define EOF (-1)

extern bool serial_debug;

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

