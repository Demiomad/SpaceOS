#include <pic.h>
#include <stdint.h>
#include <system.h>

#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1

void pic_remap(uint8_t offset1, uint8_t offset2) {
    uint8_t a1, a2;
    
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);
    
    outb(PIC1_CMD, 0x11);
    outb(PIC2_CMD, 0x11);
    outb(PIC1_DATA, offset1);
    outb(PIC2_DATA, offset2);
    outb(PIC1_DATA, 4);
    outb(PIC2_DATA, 2);
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
};

void pic_mask_all(void) {
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
};

void pic_unmask(uint8_t irq) {
    uint16_t port;
    uint8_t value;
    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    value = inb(port);
    value &= ~(1 << irq);
    outb(port, value);
};