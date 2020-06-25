#include <kernel/shell/cmd.h>
#include <kernel/time.h>

int CMD_Date::execute(const char* args)
{
    UNUSED_VARIABLE(args);
    printf("%s\n", Time::get_date_formatted());
    return 0;
}
