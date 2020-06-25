#include <kernel/signals.h>

static int index = 0;

static void* singnal_handlers[10] =
{
    0,0,0,0,0,0,0,0,0,0
};

int Signals::send_signal(Signal_Type signal)
{
    for(size_t i = 0; i < 10; i++)
    {
        void (*handler)(Signal_Type sig);

        handler = reinterpret_cast<void (*)(Signal_Type sig)>(singnal_handlers[i]);
        if (handler)
        {
            handler(signal);
        }
    }

    return 0;
}

int Signals::register_recieve(void (*handler)(Signal_Type sig))
{
    singnal_handlers[index++] = reinterpret_cast<void *&>(handler);
    if(index >= 10)         /* 10 max, temp*/
        index = 0;

    return 0;
}
