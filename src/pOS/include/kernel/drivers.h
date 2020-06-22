#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <kernel/debug.h>
#include <kernel/pOS.h>

class Driver
{
public:
     virtual int load() = NULL;
     virtual int unload() = NULL;
     virtual bool isloaded() = NULL;
     virtual const char* get_name() = NULL;
};

class Drivers
{
public:
    static void add_drivers();
    static int add_driver(Driver* driver);
    static int load_drivers();
    static int unload_drivers();

private:
    static Driver* toload_drivers[1]; //need vectors - mem managing
    static Driver* loaded_drivers[1];
};

/* ALL DRIVERS */

class ExampleDriver : public Driver
{
public:
    int load();
    int unload();
    bool isloaded();
    const char* get_name();
};

#define ADD_DRIVER(driver)          \
    do {                            \
    static driver drv = driver();   \
    add_driver(&drv);               \
    } while (0)

#endif
