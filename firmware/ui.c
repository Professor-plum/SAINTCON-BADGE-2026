#include "ui.h"
#include "framebuffer.h"
#include "buttons.h"
#include <stdint.h>
#include <string.h>

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
        frame_draw_text(buffer, description_color, 70); // White color
        int sx = selected_index % 10;
        int sy = selected_index / 10;
        frame_fill_rect(78 + sx * 20, 102 + sy * 30, 16, 26, selected_color); // Highlight selected character
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 10; col++) {
                if (row * 10 + col < 26) {
                    frame_draw_char(col * 20 + 80, row * 30 + 120, 'A' + row * 10 + col, option_color);
                } else if (row * 10 + col == 26) {
                    frame_draw_char(col * 20 + 80, row * 30 + 120, '_', option_color);
                } else if (row * 10 + col == 27) {
                    frame_draw_char(col * 20 + 80, row * 30 + 120, ' ', option_color);
                } else if (row * 10 + col == 28) {
                    frame_draw_char(col * 20 + 80, row * 30 + 120, '<', option_color);
                } else if (row * 10 + col == 29) {
                    frame_draw_char(col * 20 + 80, row * 30 + 120, '>', option_color);
                }
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
                    return; // Finish input on return
                }
                buffer[buffer_index++] = selected_char;
                buffer[buffer_index] = '\0';
                if (buffer_index >= buffer_size - 1) {
                    buffer_index = buffer_size - 1;
                }
            }
            else if (selected_index == 28) { // Allow backspace if buffer is full
                if (buffer_index > 0) { 
                    buffer_index--;
                    buffer[buffer_index] = '\0';
                }            }
            else if (selected_index == 29) { // Allow return even if buffer is
                return; // Buffer full, finish input
            }
        }
    }
}


void gui_show_message(const char* title, const char* message) {
    int idx=1;
    for (const char* ptr = message; *ptr; ptr++) {
        frame_clear();
        frame_draw_text(title, title_color, 30); // Yellow color
        
        char *str = message;
        int16_t y = LCD_HEIGHT/4;
        int ccount=0;
        while (ccount < idx) {
            int line_chars = frame_calculate_text_fit(str, y);
            char temp_str[256];
            memcpy(temp_str, str, line_chars);
            temp_str[line_chars] = '\0';
            int width = frame_calculate_text_width(temp_str);
            if (ccount + line_chars > idx) {
                temp_str[idx - ccount] = '\0'; // Truncate to the current index if it exceeds
            }
            frame_draw_string((LCD_WIDTH - width) / 2, y, temp_str, description_color); // Center the text horizontally
            y += frame_get_yadvance(); // Move to the next line (height of the font + some spacing)
            ccount+=line_chars;
            str += line_chars; // Move the pointer forward by the number of characters that fit
        }

        frame_refresh();
        int delay = 30; // Base delay for each character
        if (*ptr == '\n') {
            delay = 200; // Longer delay for new lines
        } else if (*ptr == '.' || *ptr == '!' || *ptr == '?') {
            delay = 600; // Longer delay for punctuation
        }
        if (!(buttons_get_raw() & BUTTON_PRESS)) {
             sleep_ms(delay); // Only delay if no button is pressed, allowing users to skip through the text faster
        }
        else {
             sleep_ms(1); // Short delay to debounce button presses
        }
        idx++;
    }
    buttons_clear();
    while (buttons_get_and_clear() == 0) {
        sleep_ms(100);
    }
}