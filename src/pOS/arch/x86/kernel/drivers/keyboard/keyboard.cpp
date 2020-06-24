#include "include/keyboard.h"

void keyboard_handler(struct regs *r)
{
    UNUSED_VARIABLE(r);

    /* Read from the keyboard's data buffer */
    unsigned char scancode = System::inb(0x60);

    //dbgprintf("Sc: %d\n", scancode);

    KB_BUF::scan(scancode);
}
