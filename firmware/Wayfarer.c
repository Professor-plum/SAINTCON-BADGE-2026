#include <stdio.h>
#include "pico/stdio.h"
#include "pico/stdio_usb.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "bsp/framebuffer.h"
#include "bsp/buttons.h"
#include "bsp/ws2812.h"
#include "bsp/terminal.h"
#include "ui.h"
#include "bsp/config.h"
#include "bsp/eeprom.h"
#include "blink.pio.h"

const char unlock_code[] = "SC_THRUST_LOSS";
void run_main_loop();

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
    //stdio_uart_init_full(uart0, 9600, 0, 1); 
    stdio_usb_init();
    //stdio_init_all();
    terminal_init();
    console_init();
    eeprom_init();
    
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &blink_program);
    blink_pin_forever(pio, 0, offset, MB_CLK_PIN, 1);
    
    buttons_init();
    frame_init();

    //config_clear();
    if (!config_load()) { //Inital setup
        char line[512];
        
        gui_show_message("WELCOME TO PROJECT WAYFARER",boot_message);
        config_clear();
        snprintf(line, sizeof(line), intro2_message, config_get_class_name());
        gui_show_message("", line);
        for (int i=0; i<10; ++i) {
            frame_fill_rect_alpha(0, 0, LCD_WIDTH, LCD_HEIGHT, RGB565(0, 0, 0), 25);
            frame_refresh();
            sleep_ms(20);
        }
    }

    ws2812_init(pio0, 1, WS2812_PIN);
    switch(config_get_class()) {
        case 'A': ws2812_set_pattern_color((ws2812_rgb_t){0, 0, 16});break;   //Pilot = Blue
        case 'B': ws2812_set_pattern_color((ws2812_rgb_t){16, 6, 0});break;  //Engineer = Orange
        case 'C': ws2812_set_pattern_color((ws2812_rgb_t){16, 16, 16});break;   //Scientist = White
        case 'D': ws2812_set_pattern_color((ws2812_rgb_t){0, 16, 0});break;   //Soldier = Green
        case 'E': ws2812_set_pattern_color((ws2812_rgb_t){16, 6, 6});break;   //Medic = Pink
        default: ws2812_set_pattern_color((ws2812_rgb_t){16, 0, 16});    //Purple  
    }

    while (true) {
        run_main_loop();
    }
}

