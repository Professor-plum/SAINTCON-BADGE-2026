#include "terminal.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "pico/sync.h"
#include "pico/time.h"
#include "pico/stdio_usb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "config.h"
#include "pico/unique_id.h"
#include "common.h"
#include "base64.h"
#include "bsp_komihash.h"

#define CONSOLE_BUFFER_SIZE 128
#define UART_BUFFER_SIZE 512
#define DOCKING_COMMAND_QUEUE_SIZE 8
#define UART_ID uart0

static char console_buffer[CONSOLE_BUFFER_SIZE];
static size_t console_index = 0;
bool usb_banner_printed = false;
    
static char uart_buffer[UART_BUFFER_SIZE];
static size_t uart_index = 0;
static char uart_input_buffer[UART_BUFFER_SIZE];
static volatile bool uart_input_ready = false;
static struct repeating_timer uart_timer;

static char docking_command_queue[DOCKING_COMMAND_QUEUE_SIZE][UART_BUFFER_SIZE];
static size_t docking_command_head = 0;
static size_t docking_command_tail = 0;
static size_t docking_command_count = 0;

static void uart_poll(void);
static bool terminal_enqueue_docking_command(const char *command);

extern uint16_t pending_score;

void uart_poll() {
    uint32_t irq_state = save_and_disable_interrupts();
    bool ready = uart_input_ready;
    if (ready) {
        uart_input_ready = false;
    }
    restore_interrupts(irq_state);

    if (!ready) {
        return;
    }

    if (uart_input_buffer[0] == '\0') {
        return;
    }
    if (uart_input_buffer[0] != '$') {
        char dock_unlock[] = {4, 20, 8, 7, 31, 22, 4, 28, 8, 19, 5, 30, 17, 3, 0x57};
        for (int i=0;i<sizeof(dock_unlock); ++i) {
            dock_unlock[i] ^= 0x57;
        }
        terminal_send(dock_unlock);
        return;
    }
    if (strncmp(uart_input_buffer, "$UNLOCK ", 8) == 0) {
        const char *unlock_code = uart_input_buffer + 8;
        int result = config_submit(unlock_code);
        if (result == 1) {
            stdio_puts("$UNLOCK OK\r\n");
        } else if (result == 0) {
            stdio_puts("$UNLOCK ALREADY UNLOCKED\r\n");
        } else {
            stdio_puts("$UNLOCK: INVALID\r\n");
        }
        return;
    } else if (strcmp(uart_input_buffer, "$UNLOCK") == 0) {
        stdio_puts("$UNLOCK: requires unlock code argument. Usage: $UNLOCK <code>\r\n");
        return;
    }
    // The rest of these commands are only valid when the game is running, so ignore them otherwise
    if (game_running) {
        return;
    }

    terminal_enqueue_docking_command(uart_input_buffer);
}

static bool uart_timer_callback(struct repeating_timer *t) {
    (void)t;
    uart_poll();
    if (stdio_usb_connected()) {
        if (!usb_banner_printed) {
            stdio_puts("\r\n=== USB CDC connected ===\r\n");
            char cdc_unlock[] = {6, 22, 10, 17, 0, 6, 1, 10, 19, 25, 0, 13, 0x55};
            for (int i=0;i<sizeof(cdc_unlock); ++i) {
                cdc_unlock[i] ^= 0x55;
            }
            stdio_puts(cdc_unlock);
            stdio_puts("\r\n>   ");
            usb_banner_printed = true;
        }
    } else {
        usb_banner_printed = false;
    }
    return true;
}

static void uart_irq(void) {
    while (uart_is_readable(UART_ID)) {
        int ch = uart_getc(UART_ID);
        uart_putc(UART_ID, ch);
        if (ch == '\r' || ch == '\n') {
            if (uart_index == 0) {
                continue;
            }
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

void terminal_send(const char* command) {
    if (!command) {
        return;
    }

    size_t len = strlen(command);
    uart_write_blocking(UART_ID, (const uint8_t *)command, len);
    uart_write_blocking(UART_ID, (const uint8_t *)"\r\n", 2);
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
        stdio_puts(">   ");
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

    stdio_puts(">   ");
}

bool terminal_pop_docking_command(char *command, size_t max_len) {
    bool queued = false;
    uint32_t irq_state = save_and_disable_interrupts();
    if (docking_command_count > 0) {
        size_t len = strnlen(docking_command_queue[docking_command_head], max_len - 1);
        memcpy(command, docking_command_queue[docking_command_head], len);
        command[len] = '\0';
        docking_command_head = (docking_command_head + 1) % DOCKING_COMMAND_QUEUE_SIZE;
        docking_command_count--;
        queued = true;
    }
    restore_interrupts(irq_state);
    return queued;
}

static bool terminal_enqueue_docking_command(const char *command) {
    bool queued = false;
    uint32_t irq_state = save_and_disable_interrupts();
    if (docking_command_count < DOCKING_COMMAND_QUEUE_SIZE) {
        size_t len = strnlen(command, UART_BUFFER_SIZE - 1);
        memcpy(docking_command_queue[docking_command_tail], command, len);
        docking_command_queue[docking_command_tail][len] = '\0';
        docking_command_tail = (docking_command_tail + 1) % DOCKING_COMMAND_QUEUE_SIZE;
        docking_command_count++;
        queued = true;
    }
    restore_interrupts(irq_state);
    return queued;
}

void on_usb_rx(void *v) {
    int ch;
    while ((ch = getchar_timeout_us(0)) != PICO_ERROR_TIMEOUT) {
        if ((ch == '\n') || (ch == '\r')) {
            if (console_index > 0) {
                stdio_putchar('\r');
                stdio_putchar('\n');
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