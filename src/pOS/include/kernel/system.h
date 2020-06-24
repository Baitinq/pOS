#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <stdint.h>

class System
{
public:
    static uint8_t inb(uint16_t port);
    static uint16_t inw(uint16_t port);
    static uint32_t inl(uint16_t port);

    static void outb(uint16_t port, uint8_t data);
    static void outw(uint16_t port, uint16_t data);
    static void outl(uint16_t port, uint32_t data);

    static int idle_loop(void);
};

#endif
