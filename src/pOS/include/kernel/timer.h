#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include <kernel/system.h>
#include <kernel/interrupts/irq.h>

#define INPUT_CLOCK_FREQUENCY   1193180
#define TIMER_COMMAND           0x43
#define TIMER_DATA              0x40
#define TIMER_ICW               0x36

class Timer
{
public:
    static int init(void);
    static uint32_t get_ms_from_boot(void);
    static void sleep(uint32_t sec);
    static void usleep(uint32_t usec);
private:
    static int set_frequency(uint16_t frec);
    static void timer_handler(regs* reg);
    static uint16_t hz;
    static volatile uint32_t ms;
};

#endif
