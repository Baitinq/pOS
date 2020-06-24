#ifndef _TTY_H_
#define _TTY_H_

#include <string.h>
#include <kernel/vga.h>
#include <kernel/system.h>
#include <kernel/pOS.h>

class TTY
{
public:
    static int tty_initialize(void);
    static int tty_setcolor(uint8_t color);
    static int tty_putc(char c);
    static int tty_delete(unsigned int num);
    static int tty_write(const char* data, size_t size);
    static int tty_cursor_move(int x, int y);
    static int tty_scroll(int up_or_down);
private:
    static int tty_putentryat(unsigned char c, uint8_t color, size_t x, size_t y);
    static int tty_update(void);
    static int tty_cursor_updt(void);

    static size_t tty_y;
    static size_t tty_x;
    static uint8_t tty_color;
    static uint16_t* tty_buf;
    static uint16_t tty_map[VGA::VGA_WIDTH][VGA::VGA_HEIGHT];
};


#endif
