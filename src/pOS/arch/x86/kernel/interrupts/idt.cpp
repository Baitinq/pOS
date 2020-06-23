#include <kernel/interrupts/idt.h>

idt_entry_t IDT::idt_entries[NUM_IDT_ENTRIES];
idt_ptr_t idt_ptr;

int IDT::init(void) {
    memset(idt_entries, 0, sizeof(idt_entries));

    idt_ptr.base = (uint32_t)idt_entries;
    idt_ptr.limit = sizeof(idt_entries) - 1;

    PIC::init();

    IRQ::install();

    idt_flush((uint32_t)&(idt_ptr));
    asm volatile("sti");

    return 0;
}

int IDT::set_entry(int index, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entry_t& entry = idt_entries[index];

    entry.base_lo = base & 0xFFFF;
    entry.base_hi = (base >> 16) & 0xFFFF;

    entry.always0 = 0;

    entry.sel = sel;

    entry.flags = flags | 0x60;

    return 0;
}
