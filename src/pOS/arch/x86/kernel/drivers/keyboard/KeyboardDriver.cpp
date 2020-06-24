#include <kernel/drivers.h>
#include "include/keyboard.h"

static bool loaded = false;

int KeyboardDriver::load(void)
{
    KB_BUF::init();
    IRQ::install_handler(1, keyboard_handler);

    dbgprintf("loaded keyboard\n");
    loaded = true;

    return 0;
}

int KeyboardDriver::unload(void)
{
    dbgprintf("unloaded keyboard\n");
    loaded = false;
    return 0;
}

bool KeyboardDriver::isloaded(void)
{
    return loaded;
}

const char* KeyboardDriver::get_name(void)
{
    return "Keyboard";
}
