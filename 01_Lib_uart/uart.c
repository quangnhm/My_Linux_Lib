#define _DEFAULT_SOURCE

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

#include "uart.h"

int uart_init(const char *device,const uart_config_t *cfg) {
 int fd=open(device, O_RDWR | O_NOCTTY); //open uart as file

 if (fd < 0) {
  perror("open");
  return -1;
 }

 struct termios tty;

 if (tcgetattr(fd, &tty) != 0) {
  perror("tcgetattr");
  close(fd);
  return -1;
 }

 cfmakeraw(&tty);
 //baudrate
 cfsetispeed(&tty, cfg->baudrate);
 cfsetospeed(&tty, cfg->baudrate);

 tty.c_cc[VMIN] = cfg->vmin;
 tty.c_cc[VTIME] = cfg->vtime;

 if (tcsetattr(fd, TCSANOW, &tty) != 0) {
  perror("tcsetattr");
  close(fd);
  return -1;
 }

 return fd;
}
