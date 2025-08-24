section .multiboot_header
header_start:
    dd 0xe85250d6
    dd 0
    dd header_end - header_start

    dd 0xFFFFFFFF - (0xe85250d6 + 0 + (header_end - header_start)) + 1
multiboot2_fb_tag_start:
    dw 5
    dw 1
    dd multiboot2_fb_tag_end - multiboot2_fb_tag_start
    dd 0
    dd 0 
    dd 32
multiboot2_fb_tag_mbi:
    align 8
    dw 1
    dw 0
    dd 12
    dd 8
multiboot2_fb_tag_end:
multiboot2_terminator_tag_start:
    align 8
    dw 0
    dw 0
    dd 8
header_end: