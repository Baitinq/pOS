#include <kernel/drivers.h>

static bool loaded = false;

int ExampleDriver::load(void)
{
    dbgprintf("loaded example\n");
    loaded = true;
    return 0;
}

int ExampleDriver::unload(void)
{
    dbgprintf("unloaded example\n");
    loaded = false;
    return 0;
}

bool ExampleDriver::isloaded(void)
{
    return loaded;
}

const char* ExampleDriver::get_name(void)
{
    return "Example";
}
