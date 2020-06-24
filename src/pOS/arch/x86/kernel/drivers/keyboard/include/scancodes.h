#ifndef _SCANCODES_H_
#define _SCANCODES_H_

extern unsigned char scancode[128];
extern unsigned char shift_scancode[128];

#define ESC 1
#define BACKSPACE 14
#define UP_ARROW 72
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define DOWN_ARROW 80
#define LSHIFT_PRESS 42
#define RSHIFT_PRESS 54
#define LSHIFT_RELEASE 170
#define RSHIFT_RELEASE 182
#define LCTRL_PRESS 29
#define RCTRL_PRESS 29      //TODO: change
#define LCTRL_RELEASE 157
#define RCTRL_RELEASE 157   //TODO: change
#define LALT_PRESS 56
#define RALT_PRESS 56       //TODO: change?
#define LALT_RELEASE 184
#define RALT_RELEASE 184    //TODO: change?

#endif
