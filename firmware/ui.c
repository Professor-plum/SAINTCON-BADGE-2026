#include "ui.h"
#include "framebuffer.h"
#include "buttons.h"
#include <stdint.h>

static const uint16_t selected_color = RGB565(250, 250, 250);
static const uint16_t unavailable_color = RGB565(40, 40, 40);
static const uint16_t title_color = RGB565(255, 255, 0);
static const uint16_t description_color = RGB565(150, 150, 150);
static const uint16_t option_color = RGB565(150, 150, 150);

void gui_get_input(const char* prompt, char* buffer, int buffer_size) {

    int selected_index = 0;
    int buffer_index = 0;
    while (true) {
        frame_clear();
        frame_draw_text(prompt, title_color, 30); // Yellow color
        for (int i=0; i<buffer_size-1; ++i) {
            uint16_t color = (i==buffer_index) ? selected_color : option_color;
            frame_draw_char(10 + i * 20, 80, buffer[i] ? buffer[i] : '_', color); // Underscore for input
        }
        frame_fill_rect(10 + selected_index * 20, 80, 20, 30, selected_color); // Highlight selected character
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 10; col++) {
                frame_draw_char(col * 20 + 10, row * 30 + 80, 'A' + row * 10 + col, option_color);
            }
        }
        frame_refresh();

        uint32_t keys = buttons_get_and_clear();
        if (keys & BUTTON_UP) {
            selected_index = (selected_index - 10 + 30) % 30;
        }
        if (keys & BUTTON_DOWN) {
            selected_index = (selected_index + 10) % 30;
        }
        if (keys & BUTTON_LEFT) {
            selected_index = (selected_index - 1 + 30) % 30;
        }
        if (keys & BUTTON_RIGHT) {
            selected_index = (selected_index + 1) % 30;
        }
        if (keys & BUTTON_PRESS) {
            if (buffer_index < buffer_size - 1) {
                char selected_char = (selected_index < 26) ? ('A' + selected_index) : '_'; // Map 0-25 to A-Z, 26-29 to '_'
                if (selected_index == 26) selected_char = '_';
                else if (selected_index == 27) selected_char = ' ';
                else if (selected_index == 28) { //special case for backspace
                    if (buffer_index > 0) { 
                        buffer_index--;
                        buffer[buffer_index] = '\0';
                    }
                    continue; // Don't add a character for backspace

                }
                else if (selected_index == 29) { //special case for return
                    break; // Finish input on return
                }
                buffer[buffer_index++] = selected_char;
                buffer[buffer_index] = '\0';
                if (buffer_index >= buffer_size - 1) {
                    buffer_index = buffer_size - 1;
                }
            }
        }
    }
}