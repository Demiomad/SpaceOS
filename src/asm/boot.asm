bits 32
section .bss
    stack_top:
        resb 16384
    stack_end:

global start
extern kmain

section .text
start:
    push ebx
    cli
    jmp kmain
    hlt