#ifndef WS2812_H
#define WS2812_H

#include <stdint.h>
#include "hardware/pio.h"

#define WS2812_NUM_LEDS 9
#define WS2812_PIN 18

// RGB color structure
typedef struct {
    uint8_t r, g, b;
} ws2812_rgb_t;

// Initialize WS2812 PIO program
void ws2812_init(PIO pio, uint sm, uint pin);

// Send RGB data to LEDs
void ws2812_show(const ws2812_rgb_t *colors, uint num_leds);

// Set a single LED color
void ws2812_set_led(uint index, uint8_t r, uint8_t g, uint8_t b);

// Clear all LEDs
void ws2812_clear(void);

void ws2812_pattern_update(void);

void ws2812_show_alert(ws2812_rgb_t color);

#endif // WS2812_H
