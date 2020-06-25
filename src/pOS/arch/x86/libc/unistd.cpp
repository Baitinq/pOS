#include <unistd.h>

void sleep(uint32_t sec)
{
    Timer::sleep(sec);
}

void usleep(uint32_t usec)
{
    Timer::usleep(usec);
}
