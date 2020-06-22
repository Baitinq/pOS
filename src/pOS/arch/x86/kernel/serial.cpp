#include <kernel/serial.h>

int Serial::init_serial(uint16_t port)
{
   System::outb(port + 1, 0x00); //cli
   System::outb(port + 3, 0x80);
   System::outb(port + 0, 0x03);
   System::outb(port + 1, 0x00);
   System::outb(port + 3, 0x03);
   System::outb(port + 2, 0xC7);
   System::outb(port + 4, 0x0B); //sti

   return 0;
}

int Serial::is_transmit_empty(uint16_t port)
{
   return System::inb(port + 5) & 0x20;
}

int Serial::write_serial(uint8_t data, uint16_t port)
{
   while (!is_transmit_empty(port));

   System::outb(port, data);

   return 0;
}

int Serial::serial_received(uint16_t port)
{
   return System::inb(port + 5) & 1;
}

uint8_t Serial::read_serial(uint16_t port)
{
   while (!serial_received(port));

   return System::inb(port);
}

int Serial::serial_putch(char c)
{
    static bool serial_ready = false;
    static bool was_cr = false;

    if (!serial_ready)
    {
       init_serial(COM1_PORT);
       serial_ready = true;
    }

    if (c == '\n' && !was_cr)
        write_serial('\r', COM1_PORT);

    write_serial(c, COM1_PORT);

    if (c == '\r')
        was_cr = true;
    else
        was_cr = false;

    return 0;
}
