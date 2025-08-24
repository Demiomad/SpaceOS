#ifndef SERIAL_H
#define SERIAL_H
#include <stdint.h>
#include <stddef.h>
#define PORT 0x3F8

int serial_init();
void serial_writech(char ch);
void serial_writestr(char* str);
int serial_received();
int serial_is_transmit_empty();
char serial_read();

#endif