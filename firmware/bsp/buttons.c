#include "buttons.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include <stdint.h>

int b_state = 0;


void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == GPIO_BTN1) {
        b_state |= BUTTON_1; // Set bit 5 for BTN1
    } if (gpio == GPIO_BTN2) {
        b_state |= BUTTON_2; // Set bit 6 for BTN2
    } if (gpio == GPIO_JOY_PRESS) {
        b_state |= BUTTON_PRESS; // Set bit 4 for JOY_PRESS
    } if (gpio == GPIO_JOY_DOWN) {
        b_state |= BUTTON_DOWN; // Set bit 1 for JOY_DOWN
    } if (gpio == GPIO_JOY_UP) {
        b_state |= BUTTON_UP; // Set bit 0 for JOY_UP
    } if (gpio == GPIO_JOY_RIGHT) {
        b_state |= BUTTON_RIGHT; // Set bit 3 for JOY_RIGHT
    } if (gpio == GPIO_JOY_LEFT) {
        b_state |= BUTTON_LEFT; // Set bit 2 for JOY_LEFT
    }
}

void buttons_init() {

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
        raw_state |= BUTTON_1; // Set bit 5 for BTN1
    }
    if (!gpio_get(GPIO_BTN2)) {
        raw_state |= BUTTON_2; // Set bit 6 for BTN2
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