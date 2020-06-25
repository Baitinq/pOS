#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <stddef.h>

enum Signal_Type
{
    ESC_SIG,
    LEFT_ARROW_SIG,
    RIGHT_ARROW_SIG,
    UP_ARROW_SIG,
    DOWN_ARROW_SIG,
    KILL_SIG
};

class Signals
{
public:
    static int send_signal(Signal_Type signal);
    static int register_recieve(void (*handler)(Signal_Type sig));
};

#endif
