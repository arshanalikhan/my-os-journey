#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../cpu/isr.h"

void init_keyboard();
void get_app_input(char *user_buffer); // The new Kernel router!

#endif
