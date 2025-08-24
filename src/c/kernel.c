#include <gdt.h>
#include <idt.h>
#include <pic.h>
#include <serial.h>
#include <irq.h>
#include <paging.h>
#include <vbe.h>
#include <pit.h>
#include <printf.h>

void kmain(void *info_struct) {
    gdt_setup();
    idt_init();
    pic_remap(0x20, 0x28);
    pic_mask_all();
    irq_setup();
    timer_init();
    paging_init();
    serial_init();
    vbe_init(info_struct);
    while (1);
};