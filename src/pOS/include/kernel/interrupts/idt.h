#ifndef _IDT_H_
#define _IDT_H_

#include <stdint.h>
#include <stdlib.h>
#include <kernel/interrupts/pic.h>
#include <kernel/interrupts/irq.h>

#define NUM_IDT_ENTRIES 256

typedef struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;


/* ASM func */
extern "C" void idt_flush(uint32_t ptr);

class IDT
{
public:
    static int init(void);
    static int set_entry(int index, uint32_t base, uint16_t sel, uint8_t ring);
private:
    static idt_entry_t idt_entries[NUM_IDT_ENTRIES];
};

#endif
