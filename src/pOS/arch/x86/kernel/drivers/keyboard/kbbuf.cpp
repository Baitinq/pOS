#include "include/kbbuf.h"

keyboard_buffer KB_BUF::keyboard_buf;

int KB_BUF::init(void)
{
  keyboard_buf.head = keyboard_buf.buf;
  keyboard_buf.tail = keyboard_buf.buf;

  return 0;
}

int KB_BUF::scan(unsigned char code)
{
  static bool shifted = 0;
  int result = 1;

  switch(code)
  {
    case ESC:
        break;

    case BACKSPACE:
        TTY::tty_delete(1);
        break;

    case UP_ARROW:
        if(shifted)
            TTY::tty_scroll(+1);
        else
            TTY::tty_cursor_move(0, -1);
        break;

    case LEFT_ARROW:
        TTY::tty_cursor_move(-1, 0);
        break;

    case RIGHT_ARROW:
        TTY::tty_cursor_move(1, 0);
        break;

    case DOWN_ARROW:
        if(shifted)
            TTY::tty_scroll(-1);
        else
            TTY::tty_cursor_move(0, +1);
        break;

    case LSHIFT_PRESS:
    case RSHIFT_PRESS:
        shifted = true;
        break;

    case LSHIFT_RELEASE:
    case RSHIFT_RELEASE:
        shifted = false;
        break;

    default:
      if(!(code & 0x80))
      {
        if(shifted)
            keyboard_enqueue(shift_scancode[code]);
        else
            keyboard_enqueue(scancode[code]);

        result = 0;
      }
      break;
  }

  return result;
}


unsigned char KB_BUF::keyboard_dequeue(void)
{
  unsigned char c;
  if(keyboard_buf.tail == keyboard_buf.head)
    return 0;
  else
  {
    c = *keyboard_buf.tail;
    keyboard_buf.tail = keyboard_buf.buf + ((keyboard_buf.tail + 1 - keyboard_buf.buf) % KEYBUFSIZ);
    return c;
  }
}


void KB_BUF::keyboard_enqueue(unsigned char ascii)
{
  /* KB Buf not full */
  if(((keyboard_buf.head + 1 - keyboard_buf.buf) % KEYBUFSIZ) !=
     ((keyboard_buf.tail - keyboard_buf.buf) % KEYBUFSIZ))
  {
    *keyboard_buf.head = ascii;
    keyboard_buf.head = keyboard_buf.buf +
      ((keyboard_buf.head + 1 - keyboard_buf.buf) % KEYBUFSIZ);
  }
}
