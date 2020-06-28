#include <kernel/shell/cmd.h>
#include <stdio.h>
#include <kernel/debug.h>

int CMD_Test::execute()
{
    dbgprintf("args: ");
    char* arg = strtok(NULL, " ");
    do
    {
        dbgprintf("%s, ", arg);
        arg = strtok(NULL, " ");
    } while(arg);
    dbgprintf("\n");
    printf("Test!\n");
    return 0;
}
