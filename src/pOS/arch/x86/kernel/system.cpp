#include <kernel/system.h>

uint8_t System::inb(uint16_t port)
{
    uint8_t result;
    asm volatile( "inb %1, %0" : "=a"(result) : "Nd"(port));
        return result;
}

uint16_t System::inw(uint16_t port)
{
    uint16_t result;
    asm volatile( "inw %1, %0" : "=a"(result) : "Nd"(port));
        return result;
}

uint32_t System::inl(uint16_t port)
{
    uint32_t result;
    asm volatile( "inl %1, %0" : "=a"(result) : "Nd"(port));
        return result;
}

void System::outb(uint16_t port, uint8_t data)
{
   asm volatile( "outb %0, %1" : : "a"(data), "Nd"(port));
}

void System::outw(uint16_t port, uint16_t data)
{
    asm volatile ("outw %0, %1" : : "a" (data), "Nd" (port));
}

void System::outl(uint16_t port, uint32_t data)
{
    asm volatile ("outl %0, %1" : : "a" (data), "Nd" (port));
}

int System::idle_loop(void)
{
    while(1)
        asm("hlt");

    return 1;
}
