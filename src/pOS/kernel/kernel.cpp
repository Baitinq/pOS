#include <kernel/kernel.h>

extern "C" int kmain(void)
{
    #ifdef DEBUG
    Debug::set_serial_debug(true);
    #endif

    Timer::init();
    TTY::tty_initialize();

    GDT::init();
    IDT::init();
    ISRS::install();

    Drivers::load_drivers();

    /*asm volatile("mov %eax, 0x100  \t\n"
         "mov %ecx, 0x000            \t\n"
         "div %ecx                       ");*/

    printf("Welcome to pOS v%s\n", VERSION);
    dbgprintf("Hi host %d!\n", pow(3, 2));

    printf("Current time: %s (%s-%d-%d%d)\n", Time::get_date_formatted(), Time::get_month_string(), Time::get_day(), Time::get_century() - 1, Time::get_year());

    usleep(200);

    Shell::init();

    System::idle_loop();

    ASSERT(false);

    return 1;
}
