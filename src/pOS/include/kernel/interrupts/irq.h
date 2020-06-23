#ifndef _IRQ_H_
#define _IRQ_H_

#include <kernel/system.h>
#include <kernel/registers.h>
#include <kernel/interrupts/idt.h>

/* Interrupt requests */
extern "C" void irq0(void);
extern "C" void irq1(void);
extern "C" void irq2(void);
extern "C" void irq3(void);
extern "C" void irq4(void);
extern "C" void irq5(void);
extern "C" void irq6(void);
extern "C" void irq7(void);
extern "C" void irq8(void);
extern "C" void irq9(void);
extern "C" void irq10(void);
extern "C" void irq11(void);
extern "C" void irq12(void);
extern "C" void irq13(void);
extern "C" void irq14(void);
extern "C" void irq15(void);

class IRQ
{
public:
    static int install_handler(int irq, void (*handler)(struct regs *r));
    static int uninstall_handler(int irq);
    static int install(void);
private:
    static int remap(void);
};

#endif
