#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <assert.h>

class Shell
{
public:
    static int init(void);
    static void set_prefix(const char* prefix);
private:
    static int run(void);
    static int handle_cmd(const char* cmd);
    static char prefix[10];
};

#endif
