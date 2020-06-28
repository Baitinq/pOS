#include <kernel/shell/cmd.h>
#include <kernel/tty.h>
#include <kernel/debug.h>

int CMD_Clear::execute()
{
    dbgprintf("args: ");
    char* arg = strtok(NULL, " ");
    do
    {
        dbgprintf("%s, ", arg);
        arg = strtok(NULL, " ");
    } while(arg);
    dbgprintf("\n");

    TTY::tty_initialize();
    return 0;
}
