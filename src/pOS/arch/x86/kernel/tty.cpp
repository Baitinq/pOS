#include <kernel/tty.h>

size_t TTY::tty_y;
size_t TTY::tty_x;
uint8_t TTY::tty_color;
uint16_t* TTY::tty_buf;
uint16_t TTY::tty_map[VGA::VGA::VGA_WIDTH][VGA::VGA::VGA_HEIGHT];

int TTY::tty_cursor_updt(void)
{
     uint16_t indx = tty_y * VGA::VGA::VGA_WIDTH + tty_x;

     System::outb(0x3D4, 14);
     System::outb(0x3D5, indx >> 8);
     System::outb(0x3D4, 15);
     System::outb(0x3D5, indx);

     return 0;
}

int TTY::tty_scroll(void)
{
    if(tty_y + 1 >= VGA::VGA::VGA_HEIGHT)
    {
        /* move everything up */
        for(size_t x = 0; x < VGA::VGA::VGA_WIDTH; x++)
            for(size_t y = 0; y < VGA::VGA::VGA_HEIGHT - 1; y++)
                tty_map[x][y] = tty_map[x][y + 1];

        /* clear last line */
        for(size_t i = 0; i < VGA::VGA::VGA_WIDTH; i++)
            tty_map[i][VGA::VGA::VGA_HEIGHT - 1] = VGA::vga_entry(' ', tty_color);

        tty_y--;
        tty_update();
    }

    return 0;
}

int TTY::tty_update(void) /* NOT EFFICIENT */
{
    for (size_t x = 0; x < VGA::VGA::VGA_WIDTH; x++)
        for (size_t y = 0; y < VGA::VGA::VGA_HEIGHT; y++)
            tty_buf[y * VGA::VGA::VGA_WIDTH + x] = tty_map[x][y];

    tty_cursor_updt();
    tty_scroll();

    return 0;
}

int TTY::tty_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
    tty_map[x][y] = VGA::vga_entry(c, color);
    if(++tty_x >= VGA::VGA::VGA_WIDTH)
    {
        tty_x = tty_x - VGA::VGA::VGA_WIDTH;
        tty_y++;
    }

    tty_update();
    return 0;
}

int TTY::tty_initialize(void)
{
    tty_y = 0;
    tty_x = 0;
    tty_color = VGA::vga_entry_color(VGA::VGA_COLOR_GREEN, VGA::VGA_COLOR_BLACK);
    tty_buf = (uint16_t*)VGA::VGA_MEMORY;
    for (size_t y = 0; y < VGA::VGA::VGA_HEIGHT; y++)
        for (size_t x = 0; x < VGA::VGA::VGA_WIDTH; x++)
            tty_map[x][y] = VGA::vga_entry(' ', tty_color);

    tty_update();

    return 0;
}

int TTY::tty_setcolor(uint8_t color)
{
    tty_color = color;
    return 0;
}

int TTY::tty_putc(char c)
{
    if(c == '\n')
    {
        tty_x = 0;
        tty_y++;
        return 0;
    }
    else if(c == '\t')
    {
        tty_x += 4;
        return 0;
    } //add \r

    tty_putentryat((unsigned char)c, tty_color, tty_x, tty_y);

    return 0;
}

int TTY::tty_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        tty_putc(data[i]);
    return 0;
}
