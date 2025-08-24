#include <idt.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <printf.h>

typedef struct {
	uint16_t    isr_low;
	uint16_t    kernel_cs;
	uint8_t     reserved;
	uint8_t     attributes;
	uint16_t    isr_high;
} __attribute__((packed)) idt_entry_t;

__attribute__((aligned(0x10))) 
static idt_entry_t idt[256];

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;

__attribute__((noreturn))
void exception_handler(uint8_t vector) {
    __asm__ volatile ("cli");
    while (true)
        __asm__ volatile ("hlt");
};

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entry_t* entry = &idt[num];
    int low = (uint32_t)base & 0xFFFF;
    int high = (uint32_t)base >> 16;
    entry->isr_low = low;
    entry->isr_high = high;
    entry->attributes = flags;
    entry->kernel_cs = sel;
}

static bool vectors[IDT_MAX_DESCRIPTORS];

extern void* isr_stub_table[];

void idt_init() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_gate(vector, isr_stub_table[vector], 0x08, 0x8E);
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
};