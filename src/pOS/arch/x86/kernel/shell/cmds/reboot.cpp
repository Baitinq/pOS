#include <kernel/shell/cmd.h>
#include <kernel/acpi.h>

int CMD_Reboot::execute(const char* args)
{
    UNUSED_VARIABLE(args);
    ACPI::reboot();
    return 0;
}
