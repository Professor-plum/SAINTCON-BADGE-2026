#include "game.h"
#include "bsp/framebuffer.h"
#include "bsp/buttons.h"
#include "img/nebula.h"
#include "img/mapicons.h"
#include "hexutils.h"
#include <stdint.h>
#include "bsp/common.h"
#include "outposts.h"

int frame_number = 0;

const int connections[9][4] = {
    {1, 2, -1, 4}, // Outpost 0
    {3, 0, 0, 3},  // Outpost 1
    {0, 5, 0, 5}, // Outpost 2
    {-1, 4, 1, 6},  // Outpost 3
    {3, 5, 0, 8},   // Outpost 4
    {4, -1, 2, 7},  // Outpost 5
    {3, 8, 3, 8}, // Outpost 6
    {8, 5, 5, 8},  // Outpost 7
    {6, 7, 4, -1}  // Outpost 8
};


bool outpost_unlocked[9] = { false, false, false, false, false, false, false, false, false };
bool outpost_solved[9] = { false, false, false, false, false, false, false, false, false };

static int shooting_star_active = 0;
static int shooting_star_this_rand = 0;
static int shooting_star_x = 0;
static int shooting_star_y = 0;
static int shooting_star_dx = 1;
static int shooting_star_dy = 1;
static int shooting_star_length = 3;
static int shooting_star_step = 0;
static uint32_t shooting_star_rng = 0xA5A5A5A5u;

static int shooting_star_rand(void) {
    shooting_star_rng = shooting_star_rng * 1664525u + 1013904223u;
    return (int)(shooting_star_rng >> 1);
}

static int shooting_star_rand_range(int range) {
    return range > 0 ? shooting_star_rand() % range : 0;
}

void game_draw_map(int selected) {
    int intensity = 0;
    for (int i=0; i<9; ++i) {
        if (outpost_solved[i]) {
            intensity++;
        } 
    }
    //intensity is 0-9

    frame_clear();

    pseudo_random_init(0x123456);
    for (int i = 0; i < (intensity * 50); i++) {
        int xt = psuedo_random() % 360;
        int yt = psuedo_random() % 360;
        int brightness = abs(psuedo_random() % 256);
        frame_draw_pixel(xt, yt, RGB565(brightness, brightness, brightness)); // White star
    }

    if (intensity > 0) {
        int alpha = intensity * 32; // Scale intensity to 0-255
        if (alpha > 255) alpha = 255; // Cap alpha at 255
        frame_draw_image_alpha(56, 80, nebula_image_data, 128, 128, alpha); // Nebula in the background
    }

    if (!shooting_star_active && intensity > 0) {
        shooting_star_this_rand = shooting_star_rand_range(30);
        int direction = shooting_star_rand_range(3);
        shooting_star_length = 3 + shooting_star_rand_range(3);
        shooting_star_step = 0;
        if (direction == 2) {
            shooting_star_dx = -2;
            shooting_star_dy = 1;
            shooting_star_x = 40 + shooting_star_rand_range(LCD_WIDTH - 80);
        } else {
            shooting_star_dx = 2 + direction;
            shooting_star_dy = 1;
            shooting_star_x = shooting_star_rand_range(LCD_WIDTH - 80);
        }
        shooting_star_y = 40 + shooting_star_rand_range(LCD_HEIGHT-80);
        shooting_star_active = 1;
    }

    if (shooting_star_active) {
        int head_x = shooting_star_x + shooting_star_dx * shooting_star_step;
        int head_y = shooting_star_y + shooting_star_dy * shooting_star_step;

        if (shooting_star_this_rand < intensity) 
        {   
            for (int t = 0; t < shooting_star_length; ++t) {
                int px = head_x - shooting_star_dx * t;
                int py = head_y - shooting_star_dy * t;
                if (px >= 0 && px < LCD_WIDTH && py >= 0 && py < LCD_HEIGHT) {
                    uint16_t color = t == 0 ? RGB565(255, 255, 255) : RGB565(200, 180, 120);
                    frame_draw_pixel(px, py, color);
                }
            }
        }

        shooting_star_step += 3;
        if (head_x < -10 || head_x > LCD_WIDTH + 10 || head_y > LCD_HEIGHT + 10 || shooting_star_step > 10) {
            shooting_star_active = 0;
        }
    }

    const uint16_t sineLookupTable[] = {
        1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1,
        1, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0};
    absolute_time_t current_time = get_absolute_time();
    uint32_t milliseconds_since_boot = to_ms_since_boot(current_time);
    int poi_offset = sineLookupTable[(milliseconds_since_boot>>6)%32];
    const Point locs[9] = { {140, 2}, {40, 41}, {240, 41}, {0, 140}, {140, 140}, {280, 140}, {40, 239}, {240, 239}, {140, 278} };
    uint16_t route_color = RGB565(100, 255, 100);
    for (int i=0; i<9; ++i) {
        if (outpost_unlocked[i]) {
            for (int j=0; j<4; ++j) {
                int peer = connections[i][j];
                if ((peer != -1) && (peer > i) && outpost_unlocked[peer]) {
                    frame_draw_line(locs[i].x+40, locs[i].y+40, locs[peer].x+40, locs[peer].y+40, route_color);
                }
            }
        }
    }
    
    
    for (int i = 0; i < 9; i++) {
        if (outpost_solved[i]) {
            frame_draw_image(locs[i].x, locs[i].y+poi_offset, poi_solved_image_data[i], 80, 80);
        }
        else if (outpost_unlocked[i]) {
            frame_draw_image(locs[i].x, locs[i].y+poi_offset, poi_unsolved_image_data[i], 80, 80);
        }
        else {
            frame_draw_image(locs[i].x+18, locs[i].y+18, unknown_image_data, 44, 44);
        }
    }

    frame_draw_rounded_rect(locs[selected].x, locs[selected].y+poi_offset, 80, 80, RGB565(255, 255, 0));

    frame_number++;
    frame_refresh();
}


void game_run() {
    outpost_unlocked[0] = true; // Start with the first outpost unlocked
    int selected = 0;
    while (true) {
        game_draw_map(selected);
        int buttons = buttons_get_and_clear();
        if (buttons & BUTTON_UP) {
            int next = connections[selected][2];
            if (next != -1) {
                selected = next;
            }
        }
        if (buttons & BUTTON_DOWN) {
            int next = connections[selected][3];
            if (next != -1) {
                selected = next;
            }
        }
        if (buttons & BUTTON_LEFT) {
            int next = connections[selected][0];
            if (next != -1) {
                selected = next;
            }
        }
        if (buttons & BUTTON_RIGHT) {
            int next = connections[selected][1];
            if (next != -1) {
                selected = next;
            }
        }
        if (buttons & BUTTON_1) {
            if (!outpost_unlocked[selected]) {
                outpost_unlocked[selected] = true;
            } else if (!outpost_solved[selected]) {
                outpost_solved[selected] = true;
            }
            else {
                outpost_unlocked[selected] = false;
                outpost_solved[selected] = false;
            }
        }

        if (buttons & BUTTON_2) {
            switch (selected) {
                case 0: outpost_core_run(); break;
                case 1: outpost_solar_run(); break;
                case 2: outpost_comms_run(); break;
                case 3: outpost_archive_run(); break;
                case 4: outpost_mine_run(); break;
                case 5: outpost_atmos_run(); break;
                case 6: outpost_bio_run(); break;
                case 7: outpost_factory_run(); break;
                case 8: outpost_gate_run(); break;
                default: break;
            }
        }

    }
}