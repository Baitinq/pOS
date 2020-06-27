#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <kernel/physm.h>

void *malloc(size_t size);
void *calloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

int itoa(int i, char* buf, size_t len);
int atoi(const char* str);

#endif
