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

#define TERMINAL_BUFFER_SIZE 128
#define TERMINAL_PENDING_LINES 8

static char terminal_buffer[TERMINAL_BUFFER_SIZE];
static size_t terminal_index = 0;
static bool terminal_unlocked = false;
static int terminal_crew_count = 0;

static char terminal_pending[TERMINAL_PENDING_LINES][TERMINAL_BUFFER_SIZE];
static volatile int terminal_pending_head = 0;
static volatile int terminal_pending_tail = 0;
static volatile bool terminal_prompt_pending = false;
static volatile bool terminal_queue_overflow = false;
static volatile bool terminal_usb_connected_last = false;
static struct repeating_timer terminal_timer;

static void terminal_poll(void);
static void terminal_puts(const char *s);
static void terminal_handle_char(int ch);
static void terminal_poll_usb(void);

extern uint16_t pending_score;
extern char* log_entries[12];

static bool terminal_timer_callback(struct repeating_timer *t) {
    (void)t;
    terminal_poll_usb();
    terminal_poll();
    return true;
}

static void terminal_puts(const char *s) {
    uart_puts(UART_ID, s);
    if (stdio_usb_connected()) {
        stdio_puts(s);
    }
}

static void terminal_print_prompt(void) {
    terminal_puts("\r\n> ");
}

static void terminal_handle_command(char *command) {
    char cmd[TERMINAL_BUFFER_SIZE];
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
        terminal_print_prompt();
        return;
    }

    if (strcmp(cmd, "ID") == 0) {
        char response[64];
        pico_unique_board_id_t id;
        pico_get_unique_board_id(&id);
        snprintf(response, sizeof(response), "ID: %02X%02X %c %02d %s %04X\r\n", id.id[0], id.id[1], config_get_class(), config_get_score(), config_get_handle(), config_get_unlocks);
        terminal_puts(response);
    } else if (strncmp(cmd, "UNLOCK ", 7) == 0) {
        const char *unlock_code = cmd + 7;
        int result = config_submit(unlock_code);
        if (result == 1) {
            terminal_puts("UNLOCK: OK\r\n");
        } else if (result == 0) {
            terminal_puts("UNLOCK: ALREADY UNLOCKED\r\n");
        } else {
            terminal_puts("UNLOCK: INVALID\r\n");
        }
    } else if (strcmp(cmd, "UNLOCK") == 0) {
        terminal_puts("UNLOCK: requires unlock code argument. Usage: UNLOCK <code>\r\n");
    } else if (strcmp(cmd, "ADDCREW") == 0) {
        terminal_crew_count++;
        char response[64];
        snprintf(response, sizeof(response), "ADDCREW: crew count=%d\r\n", terminal_crew_count);
        terminal_puts(response);
    } else if (strcmp(cmd, "REPORT") == 0) {
        char response[96];
        snprintf(response, sizeof(response), "REPORT: scored=%d crew=%d\r\n",
                pending_score,
                terminal_crew_count);
        terminal_puts(response);
        config_redeem_score();
    } else if (strcmp(cmd, "HELP") == 0) {
        terminal_puts("Commands: ID, UNLOCK <code>, ADDCREW, REPORT, HELP, FLAG\r\n");
    } else if (strcmp(cmd, "CLEAR") == 0) {
        terminal_puts("\x1b[2J\x1b[H"); // ANSI escape code to clear screen and move cursor to home
    } else if (strncmp(cmd, "ENTRY", 6) == 0) {
        int idx = atoi(cmd + 6);
        if (idx < 0 || idx >= 12) {
            terminal_puts("ENTRY: invalid index\r\n");
        } else {
            terminal_puts(log_entries[idx]);
            }
    } else if (strcmp(cmd, "FLAG") == 0) {
        terminal_puts("FLAG: FLAG{UART1_TERMINAL_ENABLED}\r\n");
    } else {
        terminal_puts("Unknown command. Type HELP for commands.\r\n");
    }

    terminal_print_prompt();
}

static void terminal_handle_char(int ch) {
    if (ch == '\r' || ch == '\n') {
        if (terminal_index > 0) {
            terminal_buffer[terminal_index] = '\0';
            int next_tail = (terminal_pending_tail + 1) % TERMINAL_PENDING_LINES;
            if (next_tail != terminal_pending_head) {
                memcpy(terminal_pending[terminal_pending_tail], terminal_buffer, terminal_index + 1);
                terminal_pending_tail = next_tail;
            } else {
                terminal_queue_overflow = true;
            }
            terminal_index = 0;
            terminal_prompt_pending = true;
        } else {
            terminal_prompt_pending = true;
        }
    } else if (ch == '\b' || ch == 0x7F) {
        if (terminal_index > 0) {
            terminal_index--;
            uart_putc(UART_ID, '\b');
            uart_putc(UART_ID, ' ');
            uart_putc(UART_ID, '\b');
        }
    } else if (terminal_index + 1 < TERMINAL_BUFFER_SIZE) {
        terminal_buffer[terminal_index++] = (char)ch;
    }
}

static void terminal_uart_irq(void) {
    while (uart_is_readable(UART_ID)) {
        int ch = uart_getc(UART_ID);
        if (uart_is_writable(UART_ID)) {
            uart_putc(UART_ID, ch);
        }
        terminal_handle_char(ch);
    }
}

static void terminal_poll_usb(void) {
    bool connected = stdio_usb_connected();
    if (connected && !terminal_usb_connected_last) {
        stdio_puts("USB terminal connected. Type HELP for commands.\r\n");
        char unlock_code[13] = {0x12,0x02,0x1e,0x05,0x14,0x12,0x15,0x1e,0x07,0x0d,0x14,0x19,0x00};
        for (int i=0; i<11; ++i) {
            unlock_code[i] ^= 0x41;
        }
        stdio_puts(unlock_code);
        stdio_puts("\r\n");
        terminal_prompt_pending = true;
    }
    terminal_usb_connected_last = connected;

    if (!connected) {
        return;
    }
    while (true) {
        int ch = stdio_getchar_timeout_us(0);
        if (ch == PICO_ERROR_TIMEOUT || ch < 0) {
            break;
        }
        if (ch == '\r') {
            stdio_putchar('\r');
            stdio_putchar('\n');
        } else if (ch == '\n') {
            stdio_putchar('\r');
            stdio_putchar('\n');
        } else {
            stdio_putchar(ch);
        }
        terminal_handle_char(ch);
    }
}

static void terminal_poll(void) {
    while (terminal_pending_head != terminal_pending_tail) {
        char line[TERMINAL_BUFFER_SIZE];
        memcpy(line, terminal_pending[terminal_pending_head], TERMINAL_BUFFER_SIZE);
        terminal_pending_head = (terminal_pending_head + 1) % TERMINAL_PENDING_LINES;
        terminal_handle_command(line);
    }
    if (terminal_queue_overflow) {
        terminal_queue_overflow = false;
        char unlock_code[16] = {0x12,0x02,0x1e,0x12,0x08,0x06,0x0f,0x00,0x0d,0x1e,0x06,0x09,0x0e,0x12,0x15,0x00};
        for (int i=0; i<14; ++i) {
            unlock_code[i] ^= 0x41;
        }
        terminal_puts("WARNING: terminal queue overflow, some input was dropped\r\n");
        terminal_puts(unlock_code);
        terminal_puts("\r\n");
        terminal_print_prompt();
    } else if (terminal_prompt_pending) {
        terminal_prompt_pending = false;
        terminal_print_prompt();
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
    irq_set_exclusive_handler(UART0_IRQ, terminal_uart_irq);
    irq_set_enabled(UART0_IRQ, true);

    add_repeating_timer_ms(10, terminal_timer_callback, NULL, &terminal_timer);

    terminal_puts("Wayfarer terminal ready. Type HELP for commands.\r\n");
    terminal_print_prompt();
}