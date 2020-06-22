#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <kernel/system.h>

#define COM1_PORT 0x3f8
#define COM2_PORT 0x2f8
#define COM3_PORT 0x3e8
#define COM4_PORT 0x2e8

class Serial
{
public:
    static int init_serial(uint16_t port);
    static int write_serial(uint8_t data, uint16_t port);
    static uint8_t read_serial(uint16_t port);
    static int serial_putch(char c);
private:
    static int is_transmit_empty(uint16_t port);
    static int serial_received(uint16_t port);

};

#endif
