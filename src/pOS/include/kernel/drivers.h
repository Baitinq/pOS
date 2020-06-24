#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <kernel/debug.h>
#include <kernel/interrupts/irq.h>

class Driver
{
public:
     virtual int load(void) = NULL;
     virtual int unload(void) = NULL;
     virtual bool isloaded(void) = NULL;
     virtual const char* get_name(void) = NULL;
};

class Drivers
{
public:
    static void add_drivers(void);
    static int add_driver(Driver* driver);
    static int load_drivers(void);
    static int unload_drivers(void);

private:
    static Driver* toload_drivers[1]; //need vectors - mem managing
    static Driver* loaded_drivers[1];
};

/* ALL DRIVERS */

class KeyboardDriver : public Driver
{
public:
    int load(void);
    int unload(void);
    bool isloaded(void);
    const char* get_name(void);
};

#define ADD_DRIVER(driver)          \
    do {                            \
    static driver drv = driver();   \
    add_driver(&drv);               \
    } while (0)

#endif
