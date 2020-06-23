#include <kernel/interrupts/irq.h>

static void* irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

int IRQ::install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = reinterpret_cast<void *&>(handler);

    return 0;
}

int IRQ::uninstall_handler(int irq)
{
    irq_routines[irq] = 0;

    return 0;
}

/* Remaps the IRQs so they are usable */
int IRQ::remap(void)
{
    System::outb(0x20, 0x11);
    System::outb(0xA0, 0x11);
    System::outb(0x21, 0x20);
    System::outb(0xA1, 0x28);
    System::outb(0x21, 0x04);
    System::outb(0xA1, 0x02);
    System::outb(0x21, 0x01);
    System::outb(0xA1, 0x01);
    System::outb(0x21, 0x0);
    System::outb(0xA1, 0x0);

    return 0;
}

int IRQ::install(void)
{

    remap();

    /* Do with macro */
    IDT::set_entry(32, (unsigned)irq0, 0x08, 0x8E);
    IDT::set_entry(33, (unsigned)irq1, 0x08, 0x8E);
    IDT::set_entry(34, (unsigned)irq2, 0x08, 0x8E);
    IDT::set_entry(35, (unsigned)irq3, 0x08, 0x8E);
    IDT::set_entry(36, (unsigned)irq4, 0x08, 0x8E);
    IDT::set_entry(37, (unsigned)irq5, 0x08, 0x8E);
    IDT::set_entry(38, (unsigned)irq6, 0x08, 0x8E);
    IDT::set_entry(39, (unsigned)irq7, 0x08, 0x8E);

    IDT::set_entry(40, (unsigned)irq8, 0x08, 0x8E);
    IDT::set_entry(41, (unsigned)irq9, 0x08, 0x8E);
    IDT::set_entry(42, (unsigned)irq10, 0x08, 0x8E);
    IDT::set_entry(43, (unsigned)irq11, 0x08, 0x8E);
    IDT::set_entry(44, (unsigned)irq12, 0x08, 0x8E);
    IDT::set_entry(45, (unsigned)irq13, 0x08, 0x8E);
    IDT::set_entry(46, (unsigned)irq14, 0x08, 0x8E);
    IDT::set_entry(47, (unsigned)irq15, 0x08, 0x8E);

    return 0;
}

extern "C" void irq_handler(struct regs *r)
{
    void (*handler)(struct regs *r);

    handler = reinterpret_cast<void (*)(struct regs *r)>(irq_routines[r->int_no - 32]);
    if (handler)
    {
        handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if (r->int_no >= 40)
    {
        System::outb(0xA0, 0x20);
    }

    /* EOI to the master interrupt controller */
    System::outb(0x20, 0x20);
}
