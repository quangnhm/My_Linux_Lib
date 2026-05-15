#ifndef UART_H
#define UART_H

#include <termios.h> //others

#define UART_DEV "/dev/serial0"

typedef struct {
 speed_t baudrate;
 int vmin;
 int vtime;
} uart_config_t;

int uart_init(const char *device,const uart_config_t *cfg);

#endif
