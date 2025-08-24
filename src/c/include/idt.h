#ifndef IDT_H
#define IDT_H
#define IDT_MAX_DESCRIPTORS 256

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void idt_init(void);

#endif