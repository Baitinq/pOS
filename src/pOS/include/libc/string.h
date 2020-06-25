#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str);
void* memset(void* buf, int value, size_t size);
void* memcpy(void* dst, const void* src, size_t size);
int memcmp(const void* ptr1, const void* ptr2, size_t size);
char* strncpy(char* dst, const char* src, size_t len);
char* strncat(char *dest, const char *src, size_t len);
int strncmp(const char* str1, const char* str2, size_t len);
char* strtok(char* str, const char* delim);

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

#endif
