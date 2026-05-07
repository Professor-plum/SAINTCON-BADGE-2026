#include "framebuffer.h"
#include <string.h>
//#include "GothiksRoundFont.h"
#include "gfxfont.h"
#include "CCRegeneration8pt7b.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../include/hexutils.h"
#include "pico/stdlib.h"
#include "bsp_st77916.h"

uint16_t framebuffer[LCD_WIDTH * LCD_HEIGHT];

volatile int framecounter=0;
int fps=0;
struct repeating_timer timer1;
bool flush_done_flag = true;
bsp_display_interface_t *display_if;

const GFXfont* font = &CCRegeneration8pt7b; 

bool alarm_callback(__unused struct repeating_timer *t) {
    fps = framecounter;
    framecounter = 0;
    return true; // Return true to repeat the alarm, false to cancel it
}

void flush_done(void)
{
    flush_done_flag = true;
}

void frame_init() {
    uint8_t brightness = 100;
    bsp_display_info_t display_info;
    display_info.height = LCD_WIDTH;
    display_info.width = LCD_HEIGHT;
    display_info.x_offset = 0;
    display_info.y_offset = 0;
    display_info.rotation = 0;
    display_info.brightness = brightness;
    display_info.dma_flush_done_cb = flush_done;
    bsp_display_new_st77916(&display_if, &display_info);
    display_if->init();
    add_repeating_timer_ms(-1000, alarm_callback, NULL, &timer1);
}

void frame_clear() {
    while (!flush_done_flag)
        sleep_us(100);
    flush_done_flag = false;
    memset(framebuffer, 0x00, sizeof(framebuffer));
}

inline void frame_draw_pixel(int16_t x, int16_t y, uint16_t color){
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT || x < 0 || y < 0) {
        return; // Out of bounds
    }
    framebuffer[y * LCD_WIDTH + x] = __builtin_bswap16(color); // Convert to big-endian format
}

void frame_fill_rect(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color) {
    for (uint16_t j = 0; j < height; j++) {
        for (uint16_t i = 0; i < width; i++) {
            frame_draw_pixel(x + i, y + j, color);
        }
    }
}

void frame_draw_char(int16_t x, int16_t y, char c, uint16_t color) {
    const GFXglyph* glyph = &font->glyph[c - font->first];
    const uint8_t* bitmap = &font->bitmap[glyph->bitmapOffset];

    for (uint8_t j = 0; j < glyph->height; j++) {
        for (uint8_t i = 0; i < glyph->width; i++) {
            int byte_index = (j * glyph->width + i) / 8;
            int bit_index = 7 - ((j * glyph->width + i) % 8);
            if (bitmap[byte_index] & (1 << bit_index)) {
                frame_draw_pixel(x + i + glyph->xOffset, y + j + glyph->yOffset, color);
            }
        }
    }
}

void frame_draw_string(int16_t x, int16_t y, const char* str, uint16_t color) {
    while (*str) {
        frame_draw_char(x, y, *str, color);
        const GFXglyph* glyph = &font->glyph[*str - font->first];
        x += glyph->xAdvance; // Move x for the next character
        str++;
    }
}

int frame_get_string_width(const char* str){
    int width = 0;
    while (*str) {
        const GFXglyph* glyph = &font->glyph[*str - font->first];
        width += glyph->xAdvance; // Add the advance of each character
        str++;
    }
    return width;
}

void frame_draw_string_centered(int16_t y, const char* str, uint16_t color) {
    int str_width = frame_get_string_width(str);
    uint16_t x = (LCD_WIDTH - str_width) / 2; // Center the string horizontally
    frame_draw_string(x, y, str, color);
}

int frame_calculate_max_width(int y) {
    //Display is a circle, so the maximum width at a given y can be calculated using the circle equation: x^2 + y^2 = r^2
    int radius = LCD_WIDTH/2; // Radius of the circular display
    //y starts at base of text so we adjust to the center of the text by adding half the height of the font (assuming 16 pixels for the font height)
    y -= font->yAdvance / 2;
    int max_width = 2 * (int)sqrt(radius * radius - (y - radius) * (y - radius)); // Calculate the maximum width at the given y
    return max_width;
}

char* frame_draw_string_fit(int16_t x, int16_t y, const char* str, uint16_t color, uint16_t max_width) {
    const char* start = str;
    const char* last_fit = str;
    int current_width = 0;

    while (*str) {
        const GFXglyph* glyph = &font->glyph[*str - font->first];
        if (current_width + glyph->xAdvance > max_width) {
            break; // Stop if adding the next character exceeds max width
        }
        current_width += glyph->xAdvance;
        str++;
        if ((*str == ' ') || (*str == '\0')) {
            last_fit = str; // Update last fit to the last space
        }
    }

    if (last_fit == start) {
        last_fit = str; // If no space was found, break at the current character
    }

    // Draw the substring that fits within max_width
    char temp_str[256]; // Temporary buffer for the substring
    int len = last_fit - start; // Length of the substring
    strncpy(temp_str, start, len);
    temp_str[len] = '\0'; // Null-terminate the substring

    frame_draw_string_centered(y, temp_str, color);
    return (char*)last_fit; // Return pointer to the remaining string that didn't fit
}


char* frame_string_find_fit(char* str, uint16_t y) {
    const char* start = str;
    const char* last_fit = str;
    int current_width = 0;
    int max_width = frame_calculate_max_width(y); // Calculate max width for the current line

    while (*str) {
        const GFXglyph* glyph = &font->glyph[*str - font->first];
        if (current_width + glyph->xAdvance > max_width) {
            break; // Stop if adding the next character exceeds max width
        }
        current_width += glyph->xAdvance;
        str++;
        if ((*str == ' ') || *str == '\0') {
            last_fit = str; // Update last fit to the last space
        }
    }

    if (last_fit == start) {
        last_fit = str; // If no space was found, break at the current character
    }

    return (char*)last_fit; // Return pointer to the remaining string that didn't fit
}

int frame_calculate_text_height(const char* teststr) {
    for (int lines=1; lines<15; ++lines) {
        int y = LCD_HEIGHT/2 + (lines-1) * font->yAdvance / 2; // Start y position for the first line of text
        int current_line = 0;
        const char* str = teststr; // Reset str to the beginning for each line

        while (*str)
        {
            str = frame_string_find_fit((char*)str, y); // Find the part of the string that fits within max_width
            current_line++;
            y += font->yAdvance; // Move to the next line (height of the font + some spacing)
            if (current_line >= lines) {
                break; // Stop if we've reached the maximum number of lines
            }
        }

        if ((current_line <= lines) && (*str == '\0')) {
            return lines * font->yAdvance; // Return the height needed for the text
        }
    }
    return 15 * font->yAdvance; // Return a default height if the text is too long
}


void frame_draw_long_string(int16_t x, int16_t y, const char* str, uint16_t color, uint16_t max_width) {
    while (*str)
    {
        int current_width = 0;
        const char* start = str;
        const char* last_fit = str;

        while (*str) {
            const GFXglyph* glyph = &font->glyph[*str - font->first];
            if (current_width + glyph->xAdvance > max_width) {
                break; // Stop if adding the next character exceeds max width
            }
            current_width += glyph->xAdvance;
            str++;
            if (*str == ' ') {
                last_fit = str; // Update last fit to the last space
            }
        }

        if (last_fit == start) {
            last_fit = str; // If no space was found, break at the current character
        }
        
        // Draw the substring that fits within max_width
        char temp_str[256]; // Temporary buffer for the substring
        int len = last_fit - start; // Length of the substring
        strncpy(temp_str, start, len);
        temp_str[len] = '\0'; // Null-terminate the substring

        frame_draw_string(x, y, temp_str, color);
        y += font->yAdvance; // Move to the next line (height of the font + some spacing)
        str = last_fit; // Move to the next part of the string for the next iteration
    }
}

int frame_draw_text(const char* str, uint16_t color, int16_t y) {
    int total_height = 0;
    while (*str) {
        int max_width = frame_calculate_max_width(y);
        str = frame_draw_string_fit((LCD_WIDTH- max_width) / 2, y, str, color, max_width); // Center the text horizontally
        y += font->yAdvance; // Move to the next line (height of the font + some spacing)
        total_height += font->yAdvance;
    }
    return total_height;
}



void frame_draw_text_overflow(const char* str, uint16_t color, int16_t y_offset) {
    int text_height = frame_calculate_text_height(str);
    
    int y = LCD_HEIGHT/2 - (text_height / 2) + font->yAdvance; // Center the text vertically
    while (*str) {
        int max_width = frame_calculate_max_width(y);
        str = frame_draw_string_fit((LCD_WIDTH - max_width) / 2, y + y_offset, str, color, max_width); // Center the text horizontally
        y += font->yAdvance; //Move to the next line (height of the font + some spacing)
    }
}

void frame_draw_horizontal_line(int16_t x, int16_t y, uint16_t width, uint16_t color) {
    for (uint16_t i = 0; i < width; i++) {
        frame_draw_pixel(x + i, y, color);
    }
}

void frame_draw_vertical_line(int16_t x, int16_t y, uint16_t height, uint16_t color) {
    for (uint16_t j = 0; j < height; j++) {
        frame_draw_pixel(x, y + j, color);
    }
}

void frame_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    // Bresenham's line algorithm
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */  
    while (1) {
        frame_draw_pixel(x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y1 += sy; } /* e_xy+e_y < 0 */
    }
}

void frame_draw_image(int16_t x, int16_t y, const uint16_t* image_data, uint16_t width, uint16_t height) {
    for (uint16_t j = 0; j < height; j++) {
        for (uint16_t i = 0; i < width; i++) {
            uint16_t color = image_data[j * width + i];
            if (color != 0x0000) { // Assuming 0x0000 is the transparent color
                frame_draw_pixel(x + i, y + j, color);
            }
        }
    }
}

const double sqrt3 = 1.73205080757; // Pre-calculated value of sqrt(3)

void frame_draw_hexagon(int16_t x, int16_t y, uint16_t size, uint16_t color) {
    //draw the outline of the hexagon
    double hex_height = sqrt3 * size; // Height of the hexagon
    double hex_width = size * 2;
    int vertices[6][2] = {
        {x + size, y},
        {x + size/2, y + hex_height/2},
        {x - size/2, y + hex_height/2},
        {x - size, y},
        {x - size/2, y - hex_height/2},
        {x + size/2, y - hex_height/2}
    };
    for (int i = 0; i < 6; i++) {
        int x1 = vertices[i][0];
        int y1 = vertices[i][1];
        int x2 = vertices[(i + 1) % 6][0];
        int y2 = vertices[(i + 1) % 6][1];
        frame_draw_line(x1, y1, x2, y2, color);
    }   
}

void frame_draw_hexagon_grid(int16_t x, int16_t y, uint16_t size, uint16_t color) {
    int grid_radius = 10; // Number of hexagons from the center to the edge of the grid
    for (int q = -grid_radius; q <= grid_radius; q++) {
        for (int r = -grid_radius; r <= grid_radius; r++) {
            if (abs(q + r) > grid_radius) {
                continue; // Skip hexagons that are outside the grid radius
            }
            Point at = hex_to_pixel((Hex){q,r}, size);
            if (x + at.x < 0 || x + at.x >= LCD_WIDTH || y + at.y < 0 || y + at.y >= LCD_HEIGHT) {
                continue; // Skip hexagons that are out of bounds
            }
            frame_draw_hexagon(x+at.x, y+at.y, size, color);
        }
    }
}


void frame_refresh() {
    if (fps/100) {
        frame_draw_char(270, 312, '0' + (fps/100), RGB565(0,200,0));
    }
    frame_draw_char(280, 312, '0' + (fps/10)%10, RGB565(0,200,0));
    frame_draw_char(290, 312, '0' + (fps%10), RGB565(0,200,0));
    bsp_display_area_t area = {
        .x1 = 0,
        .x2 = LCD_WIDTH - 1,
        .y1 = 0,
        .y2 = LCD_HEIGHT - 1,
    };
    display_if->flush_dma(&area, framebuffer);
    framecounter++;
}