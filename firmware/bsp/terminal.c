#include "terminal.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "pico/time.h"
#include "pico/stdio_usb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "config.h"
#include "pico/unique_id.h"
#include "common.h"

#define CONSOLE_BUFFER_SIZE 128
#define UART_BUFFER_SIZE 512
#define UART_ID uart0

static char console_buffer[CONSOLE_BUFFER_SIZE];
static size_t console_index = 0;
static char uart_buffer[UART_BUFFER_SIZE];
static size_t uart_index = 0;
static char uart_input_buffer[UART_BUFFER_SIZE];
static bool uart_input_ready = false;
static struct repeating_timer uart_timer;

static void uart_poll(void);

extern uint16_t pending_score;
extern game_character_t crew[5];
extern int crew_count;

void parse_crew_string(char* str) {
    crew_count = 0;
    char* ptr = str;
    for (int i=0; i<5; ++i) {
        while(*ptr == ' ') ++ptr;
        if (strnlen(ptr, 22) < 21) {
            break;
        }
        if ((*ptr < 'A') || (*ptr > 'E')) {
            break;
        }
        crew[i].level=1;
        crew[i].specialty=*ptr++;
        memcpy(crew[i].id, ptr, 4);
        ptr+=4;
        memcpy(crew[i].name, ptr, 15);
        crew[i].skin_tone = *(uint16_t*)crew[i].id;
        ptr+=16;
        crew_count++;
    }
    if (crew_count == 5) {
        config_achievement(fully_crew);
        int unique=true;
        for (int i=0; i<4; ++i) {
            for (int j=i+1; j<5; ++j) {
                if (crew[i].specialty == crew[j].specialty){
                    unique=false;
                }
            }
        }
        if (unique) {
            config_achievement(unique_crew);
        }
    }
    if (crew_count == 0) {
        crew[0].level=1;
        crew[0].specialty = config_get_class();
        memcpy(crew[0].name, config_get_handle(), 15);
        crew_count = 1;
    }
}

void uart_poll() {
    if (uart_input_ready) {
        uart_input_ready = false;
        if (uart_input_buffer[0] != '$') {
            return;
        }
        if (strcmp(uart_input_buffer, "$UNLOCK") == 0) {
            const char *unlock_code = uart_input_buffer + 8;
            int result = config_submit(unlock_code);
            if (result == 1) {
                stdio_puts("$UNLOCK OK\r\n");
            } else if (result == 0) {
                stdio_puts("$UNLOCK ALREADY UNLOCKED\r\n");
            } else {
                stdio_puts("$UNLOCK: INVALID\r\n");
            }
        }
        // The rest of these commands are only valid when the game is running, so ignore them otherwise
        if (game_running) {
            return;
        }
        
        if (strcmp(uart_input_buffer, "$STATION") == 0) {
            
        }
        else if (strcmp(uart_input_buffer, "$DIALOG") == 0) {
            
        }
        else if (strcmp(uart_input_buffer, "$OPTIONS") == 0) {
            
        }
        else if (strcmp(uart_input_buffer, "$CREW") == 0) {
            parse_crew_string(uart_input_buffer + 6);
        }
    }
}

static bool uart_timer_callback(struct repeating_timer *t) {
    (void)t;
    uart_poll();
    return true;
}

static void uart_irq(void) {
    while (uart_is_readable(UART_ID)) {
        int ch = uart_getc(UART_ID);
        //don't echo uart
        if (ch == '\r') {
        } else if (ch == '\n') {
            size_t len = uart_index < UART_BUFFER_SIZE ? uart_index : UART_BUFFER_SIZE - 1;
            memcpy(uart_input_buffer, uart_buffer, len);
            uart_input_buffer[len] = '\0';
            uart_input_ready = true;
            uart_index = 0;
        } else if (ch == '\b' || ch == 0x7F) {
            if (uart_index > 0) {
                uart_index--;
            }
        } else {
            if (uart_index + 1 < UART_BUFFER_SIZE) {
                uart_buffer[uart_index++] = (char)ch;
            }
        }
    }
}

void terminal_init() {
    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    uart_set_irq_enables(UART_ID, true, false);
    irq_set_exclusive_handler(UART0_IRQ, uart_irq);
    irq_set_enabled(UART0_IRQ, true);

    add_repeating_timer_ms(10, uart_timer_callback, NULL, &uart_timer);
}

static void console_handle_command(char *command) {
    char cmd[CONSOLE_BUFFER_SIZE];
    size_t len = strlen(command);
    size_t out = 0;

    while (len > 0 && (command[len - 1] == '\r' || command[len - 1] == '\n' || command[len - 1] == ' ' || command[len - 1] == '\t')) {
        len--;
    }

    for (size_t i = 0; i < len && out < sizeof(cmd) - 1; ++i) {
        cmd[out++] = toupper((unsigned char)command[i]);
    }
    cmd[out] = '\0';

    if (out == 0) {
        stdio_puts("\r\n>   ");
        return;
    }

    if (strncmp(cmd, "UNLOCK ", 7) == 0) {
        const char *unlock_code = cmd + 7;
        int result = config_submit(unlock_code);
        if (result == 1) {
            stdio_puts("UNLOCK: OK\r\n");
        } else if (result == 0) {
            stdio_puts("UNLOCK: ALREADY UNLOCKED\r\n");
        } else {
            stdio_puts("UNLOCK: INVALID\r\n");
        }
    } else if (strcmp(cmd, "UNLOCK") == 0) {
        stdio_puts("UNLOCK: requires unlock code argument. Usage: UNLOCK <code>\r\n");
    } else if (strcmp(cmd, "HELP") == 0) {
        stdio_puts("Commands: UNLOCK <code>, HELP\r\n");
    } else if (strcmp(cmd, "CLEAR") == 0) {
        stdio_puts("\x1b[2J\x1b[H"); // ANSI escape code to clear screen and move cursor to home
    } else if (strcmp(cmd, "FLAG") == 0) {
        stdio_puts("FLAG: FLAG{UART1_TERMINAL_ENABLED}\r\n");
    } else {
        stdio_puts("Unknown command. Type HELP for commands.\r\n");
    }

    stdio_puts("\r\n>   ");
}

void on_usb_rx(void *v) {
    int ch;
    while ((ch = getchar_timeout_us(0)) != PICO_ERROR_TIMEOUT) {
        if (ch == '\r') {
        } else if (ch == '\n') {
            stdio_putchar('\r');
            stdio_putchar('\n');
            if (console_index > 0) {
                console_buffer[console_index] = '\0';
                console_handle_command(console_buffer);
                console_index = 0;
            }
        } else if (ch == '\b' || ch == 0x7F) {
            if (console_index > 0) {
                console_index--;
                stdio_putchar('\b');
                stdio_putchar(' ');
                stdio_putchar('\b');
            }
        } else {
            stdio_putchar(ch);
            if (console_index + 1 < CONSOLE_BUFFER_SIZE) {
                console_buffer[console_index++] = (char)ch;
            }
        }
    }
}

void console_init() {
    stdio_set_chars_available_callback(on_usb_rx, NULL);
}