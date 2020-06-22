#include <kernel/system.h>

uint8_t System::inb(uint16_t port)
{
    uint8_t result;
    asm volatile( "inb %1, %0" : "=a"(result) : "Nd"(port));
        return result;
}

void System::outb(uint16_t port, uint8_t data)
{
   asm volatile( "outb %0, %1" : : "a"(data), "Nd"(port));
}

int System::idle_loop(void)
{
    while(1)
        asm("hlt");

    return 1;
}
