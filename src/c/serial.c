#include <serial.h>
#include <system.h>

int serial_init() {
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x80);
    outb(PORT + 0, 0x03);
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x03);
    outb(PORT + 2, 0xC7);
    outb(PORT + 4, 0x08);
    outb(PORT + 4, 0x1E);
    outb(PORT + 0, 0xAE);

    if (inb(PORT + 0) != 0xAE)
        return 1;

    outb(PORT + 4, 0x0F);
}

int serial_received() {
    return inb(PORT + 5) & 1;
}

char serial_read() {
    while (serial_received() == 0);

    return inb(PORT);
}

int serial_is_transmit_empty() {
    return inb(PORT + 5) & 0x20;
}

void serial_writech(char ch) {
    while (serial_is_transmit_empty() == 0);

    outb(PORT, ch);
}

void serial_writestr(char *str) {
    int i = 0;

    while (str[i]) {
        serial_writech(str[i]);
        i++;
    }
}