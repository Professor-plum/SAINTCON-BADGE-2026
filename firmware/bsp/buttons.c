#include "buttons.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include <stdint.h>
#include "config.h"

#define BUTTON_DEBOUNCE_MS 50

static uint64_t last_button_time[7] = {0};
static uint64_t last_button_activity_us = 0;
int b_state = 0;

static int gpio_to_button_index(uint gpio) {
    switch (gpio) {
        case GPIO_BTN1:      return 0;
        case GPIO_BTN2:      return 1;
        case GPIO_JOY_PRESS: return 2;
        case GPIO_JOY_DOWN:  return 3;
        case GPIO_JOY_UP:    return 4;
        case GPIO_JOY_RIGHT: return 5;
        case GPIO_JOY_LEFT:  return 6;
        default:             return -1;
    }
}

static int gpio_to_button_mask(uint gpio) {
    switch (gpio) {
        case GPIO_BTN1:      return BUTTON_B;
        case GPIO_BTN2:      return BUTTON_A;
        case GPIO_JOY_PRESS: return BUTTON_PRESS;
        case GPIO_JOY_DOWN:  return BUTTON_DOWN;
        case GPIO_JOY_UP:    return BUTTON_UP;
        case GPIO_JOY_RIGHT: return BUTTON_RIGHT;
        case GPIO_JOY_LEFT:  return BUTTON_LEFT;
        default:             return 0;
    }
}

int konami_seq = 0;

static bool should_accept_event(uint gpio) {
    int index = gpio_to_button_index(gpio);
    if (index < 0) {
        return false;
    }
    uint64_t now = time_us_64();
    uint64_t elapsed = now - last_button_time[index];
    if (elapsed < (uint64_t)BUTTON_DEBOUNCE_MS * 1000ULL) {
        return false;
    }
    last_button_time[index] = now;
    return true;
}

void gpio_callback(uint gpio, uint32_t events) {
    if (!should_accept_event(gpio)) {
        return;
    }
    last_button_activity_us = time_us_64();
    int mask = gpio_to_button_mask(gpio);
    if (mask) {
        b_state |= mask;
        switch (konami_seq) {
        case 0: 
        case 1:
            if (gpio == GPIO_JOY_UP) konami_seq++;
            else konami_seq = 0;
            break;
        case 2:
        case 3:
            if (gpio == GPIO_JOY_DOWN) konami_seq++;
            else konami_seq = 0;
            break;
        case 4:
        case 6:
            if (gpio == GPIO_JOY_LEFT) konami_seq++;
            else konami_seq = 0;
            break;
        case 5:
        case 7:
            if (gpio == GPIO_JOY_RIGHT) konami_seq++;
            else konami_seq = 0;
            break;
        case 8:
            if (gpio == GPIO_BTN1) konami_seq++;
            else konami_seq = 0;
            break;
        case 9:
            if (gpio == GPIO_BTN2) {
                konami_seq++;
            }
            else konami_seq = 0;
            break;
        default:
            break;
        }
    }
}

void buttons_init() {
    last_button_activity_us = time_us_64();

    gpio_init(GPIO_BTN1);
    gpio_set_dir(GPIO_BTN1, GPIO_IN);
    gpio_pull_up(GPIO_BTN1);

    gpio_init(GPIO_BTN2);
    gpio_set_dir(GPIO_BTN2, GPIO_IN);
    gpio_pull_up(GPIO_BTN2);

    gpio_init(GPIO_JOY_PRESS);
    gpio_set_dir(GPIO_JOY_PRESS, GPIO_IN);
    gpio_pull_up(GPIO_JOY_PRESS);

    gpio_init(GPIO_JOY_DOWN);
    gpio_set_dir(GPIO_JOY_DOWN, GPIO_IN);
    gpio_pull_up(GPIO_JOY_DOWN);

    gpio_init(GPIO_JOY_UP);
    gpio_set_dir(GPIO_JOY_UP, GPIO_IN);
    gpio_pull_up(GPIO_JOY_UP);

    gpio_init(GPIO_JOY_RIGHT);
    gpio_set_dir(GPIO_JOY_RIGHT, GPIO_IN);
    gpio_pull_up(GPIO_JOY_RIGHT);

    gpio_init(GPIO_JOY_LEFT);
    gpio_set_dir(GPIO_JOY_LEFT, GPIO_IN);
    gpio_pull_up(GPIO_JOY_LEFT);

    gpio_set_irq_enabled_with_callback(GPIO_BTN1, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(GPIO_BTN2, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(GPIO_JOY_PRESS, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(GPIO_JOY_DOWN, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(GPIO_JOY_UP, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(GPIO_JOY_RIGHT, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(GPIO_JOY_LEFT, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
}

void buttons_clear() {
    b_state = 0;
}

int buttons_get() {
    return b_state;
}

int buttons_get_and_clear() {
    int current_state = b_state;
    b_state = 0; // Clear the state after reading
    return current_state;
}

int buttons_get_raw() {
    int raw_state = 0;
    if (!gpio_get(GPIO_BTN1)) {
        raw_state |= BUTTON_B; // Set bit 5 for BTN1
    }
    if (!gpio_get(GPIO_BTN2)) {
        raw_state |= BUTTON_A; // Set bit 6 for BTN2
    }
    if (!gpio_get(GPIO_JOY_PRESS)) {
        raw_state |= BUTTON_PRESS; // Set bit 4 for JOY_PRESS
    }
    if (!gpio_get(GPIO_JOY_DOWN)) {
        raw_state |= BUTTON_DOWN; // Set bit 1 for JOY_DOWN
    }
    if (!gpio_get(GPIO_JOY_UP)) {
        raw_state |= BUTTON_UP; // Set bit 0 for JOY_UP
    }
    if (!gpio_get(GPIO_JOY_RIGHT)) {
        raw_state |= BUTTON_RIGHT; // Set bit 3 for JOY_RIGHT
    }
    if (!gpio_get(GPIO_JOY_LEFT)) {
        raw_state |= BUTTON_LEFT; // Set bit 2 for JOY_LEFT
    }
    return raw_state;
}

uint64_t buttons_get_last_activity_us() {
    if (konami_seq == 10) {
        konami_seq = 0;
        config_achievement(konami);
    }
    return last_button_activity_us;
}