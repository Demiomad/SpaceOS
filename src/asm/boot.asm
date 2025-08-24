bits 32
section .bss
    stack_top:
        resb 16384
    stack_end:

global _start
_start:
    mov esp, stack_end

global start
extern kmain

section .text
start:
    mov esp, stack_end
    xor ebp, ebp
    push ebx
    cli
    jmp kmain
    hlt