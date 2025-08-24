#ifndef VBE_H
#define VBE_H
#include <stdint.h>
#include <multiboot2.h>

static struct multiboot_tag_framebuffer *vbe_fb;

void vbe_init(void* info_struct);
void set_pixel(int color, int x, int y);

#endif