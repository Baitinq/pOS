#ifndef _GDT_H_
#define _GDT_H_

#include <stdint.h>
#include <stdlib.h>

#define GDT_NUM_DESCRIPTORS 8

typedef struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

/* ASM func */
extern "C" void gdt_flush(uint32_t gdt_ptr);

class GDT
{
public:
    static int init(void);
    static int set_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
private:
    static gdt_entry_t gdt_entries[GDT_NUM_DESCRIPTORS];
};

#endif
