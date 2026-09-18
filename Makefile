TARGET := dove
BUILD := build

CC := gcc
LD := ld
AS := gcc

CFLAGS := -m32 -ffreestanding -fno-stack-protector -fno-pie -nostdlib -nostdinc -Wall -Wextra -Werror -O2
ASFLAGS := -m32 -ffreestanding -fno-pie -nostdlib -nostdinc
LDFLAGS := -m elf_i386 -T linker/kernel.ld

KERNEL_OBJS := $(BUILD)/boot.o $(BUILD)/kernel.o
KERNEL := $(BUILD)/$(TARGET).elf
ISO := $(BUILD)/$(TARGET).iso

.PHONY: all clean iso run check

all: iso

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/boot.o: boot/boot.S | $(BUILD)
	$(AS) $(ASFLAGS) -c $< -o $@

$(BUILD)/kernel.o: kernel/kernel.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): $(KERNEL_OBJS) linker/kernel.ld
	$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJS)

iso: $(KERNEL)
	mkdir -p $(BUILD)/isodir/boot/grub
	cp $(KERNEL) $(BUILD)/isodir/boot/$(TARGET).elf
	cp grub/grub.cfg $(BUILD)/isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) $(BUILD)/isodir >/dev/null 2>&1

check: $(KERNEL)
	grub-file --is-x86-multiboot2 $(KERNEL)

run: iso
	qemu-system-i386 -cdrom $(ISO) -serial stdio

clean:
	rm -rf $(BUILD)
