#include <system.h>
#include <stdint.h>
#include <stddef.h>

uint8_t inb(uint16_t _port)
{
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outb(uint16_t _port, uint8_t _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

uint8_t *sys_memcpy(uint8_t *dst, uint8_t *src, int count) {
    for (int i = 0; i < count; i++) {
        dst[i] = src[i];
    }
    return dst;
}

uint8_t *sys_memset(uint8_t *dst, uint8_t val, int count) {
    for (int i = 0; i < count; i++) {
        dst[i] = val;
    }
    return dst;
}

uint16_t *sys_memsetw(uint16_t *dst, uint16_t val, int count) {
    for (int i = 0; i < count; i++) {
        dst[i] = val;
    }
    return dst;
}

size_t sys_strlen(char *str) {
    size_t i = 0;

    while (str[i])
        i++;

    return i;
}