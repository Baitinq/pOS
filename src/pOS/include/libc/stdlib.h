#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

int itoa(int i, char* buf, size_t len);
int atoi(const char* str);

#endif
