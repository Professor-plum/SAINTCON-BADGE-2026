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

const char unlock_code[] = "SC_THRUST_LOSS";

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5

#define MB_CLK_PIN 6

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
"GARDEN INITIATIVE PROJECT\n"
"AUTONOMOUS PREPARATION SYSTEM\n"
"NODE STATUS: UNRESPONSIVE\n"
"\n"
"SEARCHING FOR ACTIVE RELAYS...\n"
"1 RECOVERY UNIT DETECTED\n"
"\n"
"PROJECT REACTIVATION POSSIBLE\n";


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

    show_console_ui(boot_message);
    for (int i=0; i<10; ++i) {
        frame_fill_rect_alpha(0, 0, LCD_WIDTH, LCD_HEIGHT, RGB565(0, 0, 0), 25);
        frame_refresh();
        sleep_ms(20);
    }
    
    while (true) {
        //printf("Hello, world!\n");
        game_run();
        //sleep_ms(500);
    }
}
