#include <kernel/timer.h>

uint16_t Timer::hz = 0;
volatile uint32_t Timer::ms = 0;

#include <kernel/debug.h>

int Timer::init(void)
{
    set_frequency(1000);
    IRQ::install_handler(0, Timer::timer_handler);

    return 0;
}

int Timer::set_frequency(uint16_t frec)
{
    hz = frec;
    uint16_t divisor = INPUT_CLOCK_FREQUENCY / frec;

    /* Init, Square Wave Mode, non-BCD, first transfer LSB then MSB */
    System::outb(TIMER_COMMAND, TIMER_ICW);
    System::outb(TIMER_DATA, divisor & 0xFF);
    System::outb(TIMER_DATA, (divisor >> 8) & 0xFF);

    return 0;
}

uint32_t Timer::get_ms_from_boot(void)
{
    return ms;
}

void Timer::sleep(uint32_t sec)
{
    uint32_t end = ms + sec * hz;
    while(ms < end);
}

void Timer::usleep(uint32_t usec)
{
    uint32_t end = ms + usec;
    while(ms < end);
}

void Timer::timer_handler(regs* reg)
{
    UNUSED_VARIABLE(reg);
    ms++;
}
