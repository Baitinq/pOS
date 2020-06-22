#include <stdio.h>
#include <kernel/pOS.h>
#include <kernel/time.h>
#include <kernel/debug.h>
#include <kernel/drivers.h>
#include <math.h>
#include <assert.h>

extern "C" int kmain(void)
{
    #ifdef DEBUG
    Debug::set_serial_debug(true);
    #endif
    TTY::tty_initialize();
    Drivers::load_drivers();

    printf("Welcome to pOS v%s\n", VERSION);
    dbgprintf("Hi host %d!\n", pow(3, 2));

    printf("Current time: %s (%s-%d-%d%d)\n", Time::get_date_formatted(), Time::get_month_string(), Time::get_day(), Time::get_century() - 1, Time::get_year());

    System::idle_loop();

    ASSERT(false);

	return 1;
}
