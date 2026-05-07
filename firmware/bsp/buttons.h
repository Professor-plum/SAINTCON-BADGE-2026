#ifndef BUTTONS_H
#define BUTTONS_H
#include "pico/stdlib.h"

#define BUTTON_UP    (1 << 0)
#define BUTTON_DOWN  (1 << 1)
#define BUTTON_LEFT  (1 << 2)
#define BUTTON_RIGHT (1 << 3)
#define BUTTON_PRESS (1 << 4)
#define BUTTON_1     (1 << 5)
#define BUTTON_2     (1 << 6)

#define GPIO_BTN1       16
#define GPIO_BTN2       17
#define GPIO_JOY_PRESS  19
#define GPIO_JOY_DOWN   20
#define GPIO_JOY_UP     21
#define GPIO_JOY_RIGHT  22
#define GPIO_JOY_LEFT   23

void buttons_init();
void buttons_clear();
int buttons_get();
int buttons_get_and_clear();
int buttons_get_raw();

#endif // BUTTONS_H