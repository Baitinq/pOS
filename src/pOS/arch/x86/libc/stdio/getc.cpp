#include <stdio.h>

char getc(void)
{
    char result;
    while((result = KB_BUF::keyboard_dequeue()) == 0); //Sleep
    return result;
}
