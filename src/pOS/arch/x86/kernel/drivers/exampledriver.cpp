#include <kernel/drivers.h>

static bool loaded = false;

int ExampleDriver::load()
{
    dbgprintf("loaded example\n");
    loaded = true;
    return 0;
}

int ExampleDriver::unload()
{
    dbgprintf("unloaded example\n");
    loaded = false;
    return 0;
}

bool ExampleDriver::isloaded()
{
    return loaded;
}

const char* ExampleDriver::get_name()
{
    return "Example";
}
