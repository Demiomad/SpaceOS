# SpaceOS
An operating system made in C.

### Why?
Wanted to learn OSDev basics, I got a little too far lmao

Remember that this is NOT supposed to compete with Windows or Linux, this is a **hobbyist** project, don't expect good code.

# How do I compile?
> [!note]
> On Windows, you can use WSL, I don't think grub-mkrescue or xorriso is on Windows, correct me if I'm wrong though.

Download and install these:
- A virtualizer (QEMU is recommended, altough VirtualBox or VMware might work fine)
- GCC (C compiler), NASM (Assembler) and ld (Linker)
- xorriso (To make the ISO image)
- grub-mkrescue

Once you're done installing everything, run `make` to compile and `make run` to run the OS in QEMU, if you don't wanna use QEMU or you can't install it, make a virtual machine in VirtualBox/VMware and attach the ISO to the main boot disk.

> [!warning]
> If you use Fedora/Red Hat, change any references of grub-mkrescue in the Makefile to grub2-mkrescue

# The code sucks lmao
I know.