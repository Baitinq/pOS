#include <kernel/shell/cmd.h>
#include <kernel/time.h>
#include <kernel/debug.h>

int CMD_Date::execute()
{
    dbgprintf("args: ");
    char* arg = strtok(NULL, " ");
    do
    {
        dbgprintf("%s, ", arg);
        arg = strtok(NULL, " ");
    } while(arg);
    dbgprintf("\n");

    printf("%s\n", Time::get_date_formatted());
    return 0;
}
