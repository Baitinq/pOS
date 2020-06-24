#include <kernel/tty.h>

size_t TTY::tty_y;
size_t TTY::tty_x;
uint8_t TTY::tty_color;
uint16_t* TTY::tty_buf;
uint16_t TTY::tty_map[VGA::VGA_WIDTH][VGA::VGA_HEIGHT];

int TTY::tty_cursor_updt(void)
{
     uint16_t indx = tty_y * VGA::VGA::VGA_WIDTH + tty_x;

     System::outb(0x3D4, 14);
     System::outb(0x3D5, indx >> 8);
     System::outb(0x3D4, 15);
     System::outb(0x3D5, indx);

     return 0;
}

int TTY::tty_cursor_move(int x, int y)
{
    tty_x += x;
    tty_y += y;

    if(tty_x >= VGA::VGA_WIDTH)
        tty_x = VGA::VGA_WIDTH - 1;

    if(tty_y >= VGA::VGA_HEIGHT)
        tty_y = VGA::VGA_HEIGHT - 1;

    tty_update();

    return 0;
}

int TTY::tty_scroll(int up_or_down)
{
    /* TODO: +1 scroll up, -1 scroll down (mandatory) */
    if(up_or_down == 0 && tty_y + 1 >= VGA::VGA::VGA_HEIGHT)
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
    tty_scroll(0);

    return 0;
}

int TTY::tty_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
    if(c == '\n')
    {
        tty_x = -1;
        tty_y++;
    }
    else if(c == '\t')
    {
        tty_x += TAB_INDENTATION;
    } //add \r, delete etc
    else
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
    tty_buf = static_cast<uint16_t*>(VGA::VGA_MEMORY);
    for (size_t y = 0; y < VGA::VGA_HEIGHT; y++)
        for (size_t x = 0; x < VGA::VGA_WIDTH; x++)
            tty_map[x][y] = VGA::vga_entry(' ', tty_color); //IMPLEMENT ANOTHER CHAR FOR EMPTY STAFF SO THAT WHEN WE DELETE IT DOESNT STOP AFTER JUST 1

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
    tty_putentryat((unsigned char)c, tty_color, tty_x, tty_y);

    return 0;
}

int TTY::tty_delete(unsigned int num)
{
    int newx = tty_x;
    int newy = tty_y;

    newx--;
    if(newx < 0)
    {
        newx = VGA::VGA_WIDTH - 1;
        newy--;
        if(newy < 0)
        {
            newy = 0;
            newx = 0;
        }
    }

    tty_x = newx;
    tty_y = newy;

    tty_map[tty_x][tty_y] = VGA::vga_entry(' ', tty_color);

    num--;
    if(num > 0)
        tty_delete(num);

    tty_update();

    return 0;
}

int TTY::tty_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        tty_putc(data[i]);
    return 0;
}
