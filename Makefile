SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
ISO_DIR = isodir
GRUB_DIR = $(ISO_DIR)/boot/grub

C_SRC = $(SRC_DIR)/c/kernel.c \
        $(SRC_DIR)/c/gdt.c \
        $(SRC_DIR)/c/idt.c \
		$(SRC_DIR)/c/printf.c \
		$(SRC_DIR)/c/system.c \
		$(SRC_DIR)/c/pic.c \
		$(SRC_DIR)/c/irq.c \
		$(SRC_DIR)/c/pit.c \
		$(SRC_DIR)/c/paging.c \
		$(SRC_DIR)/c/serial.c \
		$(SRC_DIR)/c/vbe.c

ASM_SRC = $(SRC_DIR)/asm/boot.asm \
		  $(SRC_DIR)/asm/gdtasm.asm \
		  $(SRC_DIR)/asm/israsm.asm \
		  $(SRC_DIR)/asm/irqasm.asm \
		  $(SRC_DIR)/asm/pageasm.asm \
		  $(SRC_DIR)/asm/multiboot2.asm

C_OBJ = $(C_SRC:%.c=$(BUILD_DIR)/%.o)
ASM_OBJ = $(ASM_SRC:%.asm=$(BUILD_DIR)/%.o)

CC = gcc
ASM = nasm
LD = ld
EMU = qemu-system-x86_64

CFLAGS = -m32 -ffreestanding -I$(SRC_DIR)/c/include
ASMFLAGS = -f elf32
LDFLAGS = -T $(SRC_DIR)/linker.ld -m elf_i386

KERNEL_BIN = $(BIN_DIR)/kernel.bin
ISO = SpaceOS.iso

all: create

create: $(KERNEL_BIN)
	@echo "Creating GRUB directory"
	@mkdir -p $(GRUB_DIR)
	@echo "Copying compiled kernel to isodir/boot/spaceos.bin"
	@cp $(KERNEL_BIN) $(ISO_DIR)/boot/spaceos.bin
	@echo "Copying GRUB config to isodir/grub.cfg"
	@cp grub.cfg $(GRUB_DIR)/grub.cfg
	@echo "Creating ISO"
	@grub-mkrescue -o $(ISO) $(ISO_DIR)

$(KERNEL_BIN): $(C_OBJ) $(ASM_OBJ)
	@echo "Creating bin directory"
	@mkdir -p bin
	@$(LD) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< to object file $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	@echo "Compiling $< to object file $@"
	@$(ASM) $(ASMFLAGS) $< -o $@

run:
	@$(EMU) -cdrom $(ISO) -m 1G -serial mon:stdio

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR) $(ISO_DIR) $(ISO)