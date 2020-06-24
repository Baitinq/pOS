#ifndef _ACPI_H_
#define _ACPI_H_

#include <assert.h>
#include <kernel/system.h>

class ACPI
{
public:
    static void halt(void);
    static void shutdown(void);
    static void reboot(void);
};

#endif
