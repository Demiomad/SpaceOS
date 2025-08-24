#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdint.h>
#include <stddef.h>

struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

uint8_t inb(uint16_t _port);
void outb(uint16_t _port, uint8_t _data);
uint8_t *sys_memcpy(uint8_t *dst, uint8_t *src, int count);
uint8_t *sys_memset(uint8_t *dst, uint8_t val, int count);
uint16_t *sys_memsetw(uint16_t *dst, uint16_t val, int count);
size_t sys_strlen(char *str);

#endif