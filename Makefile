SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
ISO_DIR = isodir
GRUB_DIR = $(ISO_DIR)/boot/grub

C_SRC = $(shell find src/c -name '*.c')

ASM_SRC = $(shell find src/asm -name '*.asm')

C_OBJ = $(C_SRC:%.c=$(BUILD_DIR)/%.o)
ASM_OBJ = $(ASM_SRC:%.asm=$(BUILD_DIR)/%.o)

CC = gcc
ASM = nasm
LD = ld
EMU = qemu-system-x86_64

CFLAGS = -m32 -ffreestanding -I$(SRC_DIR)/c/include -fno-stack-protector -fno-stack-check -fno-lto -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -mno-avx -mno-80387
ASMFLAGS = -f elf32
LDFLAGS = -T $(SRC_DIR)/linker.ld -m elf_i386 -static -nostdlib

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