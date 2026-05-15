#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memset
#include <unistd.h>
#include <termios.h> //others
#include <errno.h>

#include "uart.h"

#define UART_DEV "/dev/serial0"
#define BAUDRATE B115200

int main(void) {
 uart_config_t cfg = {
 .baudrate = B115200,
 .vmin = 0,
 .vtime = 1
 };

 int fd = uart_init(UART_DEV, &cfg);
 if (fd < 0) return 1;

 printf("UART bridge started... \n");

 char buf[100];

 while (1) {
  int n = read(fd, buf, sizeof(buf));

  if (n > 0) {
   write(STDOUT_FILENO, buf, n);
  }
 }

 close(fd);
 return 0;
}
