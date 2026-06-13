#include <stdio.h>
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "bsp/framebuffer.h"
#include "game.h"
#include "bsp/buttons.h"
#include "bsp/ws2812.h"
#include "bsp/terminal.h"
#include "ui.h"
#include "img/icons.h"
#include "bsp/config.h"
#include "img/titlescreen.h"

const char unlock_code[] = "SC_THRUST_LOSS";

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5

#define MB_CLK_PIN 6


void run_achievement_screen();

#include "blink.pio.h"

void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq) {
    blink_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);

    printf("Blinking pin %d at %d Hz\n", pin, freq);

    // PIO counter program takes 3 more cycles in total than we pass as
    // input (wait for n + 1; mov; jmp)
    pio->txf[sm] = (125000000 / (2 * freq)) - 3;
}

const char boot_message[] = 
"Out there you'll find opportunity, adventure, and occasionally cargo that absolutely should not be opened during transit.\n"
"Complete supply runs, support station construction, and help guide humanity's expansion into the stars.\n"
"Remember: every great civilization started with someone willing to haul boxes.";

const char intro2_message[] = 
"After careful analysis of your profile, mission records, and several factors we are not at liberty to discuss, you will be assigned the roll of\n"
"%s\n"
"One final question before launch:\n"
"What name should history remember you by?";


int main()
{
    stdio_init_all();
    terminal_init();
    
    i2c_init(I2C_PORT, 400*1000); 
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &blink_program);
    printf("Loaded program at %d %p", offset, unlock_code);
    
    blink_pin_forever(pio, 0, offset, MB_CLK_PIN, 1);
    
    buttons_init();
    ws2812_init(pio0, 1, WS2812_PIN);
    
    frame_init();

    config_load();
    if (false) { //Inital setup
        gui_show_message("WELCOME TO PROJECT WAYFARER",boot_message);
        char line[512];
        snprintf(line, sizeof(line), intro2_message, config_get_class_name());
        gui_show_message("", line);
        char input_buffer[11] = {0};
        gui_get_input("Enter user name:", input_buffer, sizeof(input_buffer));
        config_set_handle(input_buffer);
        for (int i=0; i<10; ++i) {
            frame_fill_rect_alpha(0, 0, LCD_WIDTH, LCD_HEIGHT, RGB565(0, 0, 0), 25);
            frame_refresh();
            sleep_ms(20);
        }
    }
    
    while (true) {
        frame_clear();
        frame_draw_image(0,0,title_image_data,360,360);
        frame_refresh();
        int buttons = buttons_get_and_clear();
        if (buttons & BUTTON_A) {
            game_run();
        }
        else if (buttons & BUTTON_PRESS) {
            run_achievement_screen();
        }
        //sleep_ms(50);
    }
}

static const uint16_t selected_color = RGB565(80, 80, 250);
static const uint16_t unavailable_color = RGB565(40, 40, 40);
static const uint16_t title_color = RGB565(255, 255, 0);
static const uint16_t description_color = RGB565(150, 150, 150);
static const uint16_t option_color = RGB565(150, 150, 150);

void run_achievement_screen() {
    int selected_index = 0;
    while (true) {
        uint32_t unlocks = config_get_achievements();
        frame_clear();
        frame_draw_text("Achievements", title_color, 30); // Yellow color
        frame_draw_text(config_get_achievement_name(selected_index), description_color, 120); // White color
        int sx = selected_index % 8;
        int sy = selected_index / 8;
        frame_fill_rect(36 + sx * 36, 140 + sy * 36, 36, 36, selected_color); // Highlight selected character
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 8; col++) {
                const uint16_t* data = (unlocks & (1<<(row*8+col))) ? medal_image_data : locked_image_data;
                frame_draw_image(38 + col * 36, 142 + row * 36, data, 32, 32);
            }
        }
        frame_refresh();

        uint32_t keys = buttons_get_and_clear();
        if (keys & BUTTON_UP) {
            selected_index = (selected_index - 8 + 32) % 32;
        }
        if (keys & BUTTON_DOWN) {
            selected_index = (selected_index + 8) % 32;
        }
        if (keys & BUTTON_LEFT) {
            selected_index = (selected_index - 1 + 32) % 32;
        }
        if (keys & BUTTON_RIGHT) {
            selected_index = (selected_index + 1) % 32;
        }
        if (keys & BUTTON_B) {
            break;
        }
    }
}
