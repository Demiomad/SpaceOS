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
    // TIPS FOR GETTING VBE TO WORK: don't initialize paging until map page is implemented
    // or use limine, https://github.com/DemioMAD/SpaceOS/tree/limine
    gdt_setup();
    idt_init();
    pic_remap(0x20, 0x28);
    pic_mask_all();
    irq_setup();
    timer_init();
    // paging_init(); // If editing this code/making a fork of this OS, either use the limine version or implement actual paging
    serial_init();
    vbe_init(info_struct);
    while (1);
};
