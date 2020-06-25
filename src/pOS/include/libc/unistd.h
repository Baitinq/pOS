#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <kernel/timer.h>

void sleep(uint32_t sec);
void usleep(uint32_t usec);

#endif
