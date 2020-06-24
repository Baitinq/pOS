#ifndef _KBBUF_H_
#define _KBBUF_H_

#include <stdbool.h>
#include <kernel/tty.h>
#include "scancodes.h"

#define KEYBUFSIZ 128

struct keyboard_buffer
{
  unsigned char buf[KEYBUFSIZ];
  unsigned char *head;
  unsigned char *tail;
};

class KB_BUF
{
public:
    static int init(void);
    static int scan(unsigned char code);
    static void keyboard_enqueue(unsigned char ascii);
    static unsigned char keyboard_dequeue(void);
private:
    static keyboard_buffer keyboard_buf;
};

#endif