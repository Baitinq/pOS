#include <kernel/shell/cmd.h>
#include <kernel/acpi.h>

int CMD_Shutdown::execute(const char* args)
{
    UNUSED_VARIABLE(args);
    ACPI::shutdown();
    return 0;
}
