#include <kernel/shell/cmd.h>
#include <kernel/acpi.h>
#include <kernel/debug.h>

int CMD_Halt::execute()
{
    dbgprintf("args: ");
    char* arg = strtok(NULL, " ");
    do
    {
        dbgprintf("%s, ", arg);
        arg = strtok(NULL, " ");
    } while(arg);
    dbgprintf("\n");
    ACPI::halt();
    return 0;
}
