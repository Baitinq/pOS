#include <kernel/interrupts/pic.h>

int PIC::init(void) {
    /* ICW1 */
    System::outb(PIC1_COMMAND, ICW1);
    System::outb(PIC2_COMMAND, ICW1);

    /* ICW2, irq 0 to 7 is mapped to 0x20 to 0x27, irq 8 to F is mapped to 28 to 2F */
    System::outb(PIC1_DATA, 0x20);
    System::outb(PIC2_DATA, 0x28);

    /* ICW3, connect master pic with slave pic */
    System::outb(PIC1_DATA, 0x4);
    System::outb(PIC2_DATA, 0x2);

    /* ICW4, set x86 mode */
    System::outb(PIC1_DATA, 1);
    System::outb(PIC2_DATA, 1);

    /* Clear the mask register */
    System::outb(PIC1_DATA, 0);
    System::outb(PIC2_DATA, 0);

    return 0;
}

int PIC::irq_ack(uint8_t irq) {
    if(irq >= 0x28)
        System::outb(PIC2, PIC_EOI);
    System::outb(PIC1, PIC_EOI);

    return 0;
}
