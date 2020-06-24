#include <kernel/shell/cmd.h>
#include <kernel/acpi.h>

int CMD_Halt::execute(const char* args)
{
    UNUSED_VARIABLE(args);
    ACPI::halt();
    return 0;
}
