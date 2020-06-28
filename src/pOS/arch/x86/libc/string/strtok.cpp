#include <stdlib.h>
#include <string.h>

char* strtok(char* str, const char* delim)
{
    static char* lastPos = 0;
    static char token[100];

    if(!str && !lastPos)
        return 0;

    if(!delim)
        return 0;

    if(str)
        lastPos = str;

    int delim_len = strlen(delim);
    char* strt_ptr = lastPos;
    int count = 0;

    while(*lastPos != '\0')
    {
        bool is_found = false;
        for(int y = 0; y < delim_len; y++)
        {
            if(*(delim + y) == *lastPos)
                is_found = true;
        }
        lastPos++;
        if(is_found)
            break;
        count++;
    }

    if(*lastPos == '\0')
        lastPos = NULL;

    if(!count)
        return strtok(0, delim);

    for(int x = 0; x < count; x++)
        token[x] = *(strt_ptr + x);
    token[count] = '\0';

    return token;
}

