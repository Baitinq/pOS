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
  static bool ctrled = 0;
  static bool alted = 0;
  int result = 1;

  switch(code)
  {
    case ESC:
        Signals::send_signal(ESC_SIG);
        break;

    case UP_ARROW:
        Signals::send_signal(UP_ARROW_SIG);
        break;

    case LEFT_ARROW:
        Signals::send_signal(LEFT_ARROW_SIG);
        break;

    case RIGHT_ARROW:
        Signals::send_signal(RIGHT_ARROW_SIG);
        break;

    case DOWN_ARROW:
        Signals::send_signal(DOWN_ARROW_SIG);
        break;
    /* IMPLEMENT WITH SIG CODES */

    case LSHIFT_PRESS:
    case RSHIFT_PRESS:
        shifted = true;
        break;

    case LSHIFT_RELEASE:
    case RSHIFT_RELEASE:
        shifted = false;
        break;

    case LCTRL_PRESS:
    //case RCTRL_PRESS:
        ctrled = true;
        break;

    case LCTRL_RELEASE:
    //case RCTRL_RELEASE:
        ctrled = false;
        break;

    case LALT_PRESS:
    //case RALT_PRESS:
        alted = true;
        break;

    case LALT_RELEASE:
    //case RALT_RELEASE:
        alted = false;
        break;

    default:
      if(!(code & 0x80))
      {
          unsigned char ascii;
        if(shifted)
            ascii = shift_scancode[code];
        else
            ascii = scancode[code];

        if(ctrled || alted)
            handle_keybind(ascii, ctrled ? 1 : -1);
        else
            keyboard_enqueue(ascii);

        result = 0;
      }
      break;
  }

  return result;
}

int KB_BUF::handle_keybind(unsigned char ascii, int type)
{
    UNUSED_VARIABLE(ascii);
    UNUSED_VARIABLE(type);
    //if(type == 1); /* CTRL */
    //else if (type == -1); /* ALT */
    /* TODO: Signals */
    return 0;
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
