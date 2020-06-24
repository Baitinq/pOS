#include <kernel/drivers.h>

Driver* Drivers::toload_drivers[1]; //vec
Driver* Drivers::loaded_drivers[1];

void Drivers::add_drivers(void)
{
    #ifdef DRIVER_EXAMPLE
    ADD_DRIVER(KeyboardDriver);
    #endif
}

int Drivers::add_driver(Driver* driver)
{
    dbgprintf("adding driver\n");
    if(!driver->isloaded())
        toload_drivers[0] = driver;

    return 0;
}

int Drivers::load_drivers(void)
{
    dbgprintf("loading drivers\n");

    add_drivers();

    int result = 0;
    for(Driver* driver : toload_drivers)
    {
        result = driver->load();
        if(result) break;
        //add to loaded
    }

    return result;
}

int Drivers::unload_drivers(void)
{
    dbgprintf("unloading drivers\n");
    int result = 0;
    for(Driver* driver : loaded_drivers)
    {
        result = driver->unload();
        if(result) break;
        //remove from loaded
    }

    return result;
}
