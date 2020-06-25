#include <kernel/shell/cmd.h>
#include <stdio.h>

int CMD_Test::execute(const char* args)
{
    UNUSED_VARIABLE(args);
    printf("Test!\n");
    return 0;
}
