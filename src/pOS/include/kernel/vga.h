#ifndef _VGA_H_
#define _VGA_H_

#include <stdint.h>
#include <stddef.h>

class VGA
{
public:
     static constexpr int VGA_WIDTH = 80;
     static constexpr int VGA_HEIGHT = 25;
     static constexpr uint16_t* VGA_MEMORY = reinterpret_cast<uint16_t*>(0xb8000);

     enum vga_colors {
        VGA_COLOR_BLACK,
        VGA_COLOR_BLUE,
        VGA_COLOR_GREEN,
        VGA_COLOR_CYAN,
        VGA_COLOR_RED,
        VGA_COLOR_MAGENTA,
        VGA_COLOR_BROWN,
        VGA_COLOR_LIGHT_GREY,
        VGA_COLOR_DARK_GREY,
        VGA_COLOR_LIGHT_BLUE,
        VGA_COLOR_LIGHT_GREEN,
        VGA_COLOR_LIGHT_CYAN,
        VGA_COLOR_LIGHT_RED,
        VGA_COLOR_LIGHT_MAGENTA,
        VGA_COLOR_LIGHT_BROWN,
        VGA_COLOR_WHITE,
    };

    static uint8_t vga_entry_color(enum vga_colors fg, enum vga_colors bg)
    {
        return fg | bg << 4;
    }

    static uint16_t vga_entry(unsigned char uc, uint8_t color)
    {
        return (uint16_t) uc | (uint16_t) color << 8;
    }
};

#endif
