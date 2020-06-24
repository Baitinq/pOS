#include <kernel/shell/cmd.h>
#include <kernel/tty.h>

int CMD_Clear::execute(const char* args)
{
    UNUSED_VARIABLE(args);
    TTY::tty_initialize();
    return 0;
}
