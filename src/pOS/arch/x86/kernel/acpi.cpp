#include <kernel/acpi.h>

void ACPI::halt(void)
{
    asm volatile("cli   \t\n"
                 "hlt       ");
    ASSERT(false);
}

void ACPI::shutdown(void)
{
    System::outw(0x604, 0x2000); /* QEMU temp implementation */
    ASSERT(false);
}

void ACPI::reboot(void)
{
    /* 8042 reset */
    int8_t good = 0x02;
    while (good & 0x02)
        good = System::inb(0x64);
    System::outb(0x64, 0xFE);

    ASSERT(false);
}
