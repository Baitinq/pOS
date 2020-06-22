#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <stdint.h>

class System
{
public:
    static uint8_t inb(uint16_t port);
    static void outb(uint16_t port, uint8_t data);

    static int idle_loop(void);
};

#endif
