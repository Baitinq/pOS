#include <kernel/interrupts/isrs.h>

void ISRS::install(void)
{
    /* Do with macro */
    IDT::set_entry(0, (unsigned)isr0, 0x08, 0x8E);
    IDT::set_entry(1, (unsigned)isr1, 0x08, 0x8E);
    IDT::set_entry(2, (unsigned)isr2, 0x08, 0x8E);
    IDT::set_entry(3, (unsigned)isr3, 0x08, 0x8E);
    IDT::set_entry(4, (unsigned)isr4, 0x08, 0x8E);
    IDT::set_entry(5, (unsigned)isr5, 0x08, 0x8E);
    IDT::set_entry(6, (unsigned)isr6, 0x08, 0x8E);
    IDT::set_entry(7, (unsigned)isr7, 0x08, 0x8E);

    IDT::set_entry(8, (unsigned)isr8, 0x08, 0x8E);
    IDT::set_entry(9, (unsigned)isr9, 0x08, 0x8E);
    IDT::set_entry(10, (unsigned)isr10, 0x08, 0x8E);
    IDT::set_entry(11, (unsigned)isr11, 0x08, 0x8E);
    IDT::set_entry(12, (unsigned)isr12, 0x08, 0x8E);
    IDT::set_entry(13, (unsigned)isr13, 0x08, 0x8E);
    IDT::set_entry(14, (unsigned)isr14, 0x08, 0x8E);
    IDT::set_entry(15, (unsigned)isr15, 0x08, 0x8E);

    IDT::set_entry(16, (unsigned)isr16, 0x08, 0x8E);
    IDT::set_entry(17, (unsigned)isr17, 0x08, 0x8E);
    IDT::set_entry(18, (unsigned)isr18, 0x08, 0x8E);
    IDT::set_entry(19, (unsigned)isr19, 0x08, 0x8E);
    IDT::set_entry(20, (unsigned)isr20, 0x08, 0x8E);
    IDT::set_entry(21, (unsigned)isr21, 0x08, 0x8E);
    IDT::set_entry(22, (unsigned)isr22, 0x08, 0x8E);
    IDT::set_entry(23, (unsigned)isr23, 0x08, 0x8E);

    IDT::set_entry(24, (unsigned)isr24, 0x08, 0x8E);
    IDT::set_entry(25, (unsigned)isr25, 0x08, 0x8E);
    IDT::set_entry(26, (unsigned)isr26, 0x08, 0x8E);
    IDT::set_entry(27, (unsigned)isr27, 0x08, 0x8E);
    IDT::set_entry(28, (unsigned)isr28, 0x08, 0x8E);
    IDT::set_entry(29, (unsigned)isr29, 0x08, 0x8E);
    IDT::set_entry(30, (unsigned)isr30, 0x08, 0x8E);
    IDT::set_entry(31, (unsigned)isr31, 0x08, 0x8E);
}

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
const char *exception_messages[32] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

extern "C" void fault_handler(struct regs *r)
{
    if (r->int_no < 32)
    {
        REG::print_regs(r);
        printf("%s", exception_messages[r->int_no]);
        printf(" Exception. System Halted!\n");
        System::idle_loop();
    }
}
