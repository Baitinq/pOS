#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str);
void* memset(void* buf, int value, size_t size);
void* memcpy(void* dst, const void* src, size_t size);
char* strncpy(char* dst, const char* src, size_t len);
char* strncat(char *dest, const char *src, size_t len);

#endif
