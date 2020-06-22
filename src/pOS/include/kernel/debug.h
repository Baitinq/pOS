#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdarg.h>
#include <printf_internal.h>
#include <kernel/serial.h>

int dbgprintf(const char* fmt, ...);
int dbgprint(const char* str, int len);

#endif
