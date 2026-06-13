#ifndef TERMINAL_H
#define TERMINAL_H
#include "pico/stdlib.h"

// UART defines
// Use UART0 for the terminal (UART1 is not used)
#define UART_ID uart0
#define BAUD_RATE 9600

// Use pins 0 and 1 for UART0
#define UART_TX_PIN 0
#define UART_RX_PIN 1

void terminal_init(void);
void console_init(void);

#endif