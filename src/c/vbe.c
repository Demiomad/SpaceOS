#include <vbe.h>
#include <stddef.h>
#include <printf.h>
#include <multiboot2.h>

uint32_t *address;

#define ALIGN_UP(a, b) (a + (b - 1)) & ~(b - 1)

struct multiboot_tag_framebuffer *find_fb_tag(void *info_struct) {
    for (struct multiboot_tag *t = ((struct multiboot_tag *)(info_struct + 8));
        t->type != MULTIBOOT_TAG_TYPE_END;
        t = (struct multiboot_tag *)(ALIGN_UP((unsigned int)t + t->size, 8))) {
        if (t->type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER) return (struct multiboot_tag_framebuffer *)t;
    }
    return ((void *)0);
}

void vbe_init(void* info_struct) {
    vbe_fb = find_fb_tag(info_struct);
    if (vbe_fb == NULL) {
        return;
    }
    address = (multiboot_uint32_t *)vbe_fb->common.framebuffer_addr;
    // test vbe
    for (size_t i = 0; i < 100; i++) {
        set_pixel(0xFFFFFF, i, i);
    }
}

void set_pixel(int color, int x, int y) {
    int pos = (y * (vbe_fb->common.framebuffer_pitch / 4) + x);
    address[pos] = color;
}