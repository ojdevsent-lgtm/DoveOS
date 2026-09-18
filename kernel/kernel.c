#include <stdint.h>
#include <stddef.h>

#define VGA_MEMORY ((volatile uint16_t*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_COLOR 0x07

static size_t cursor_row = 0;
static size_t cursor_col = 0;

static void clear_screen(void) {
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
        VGA_MEMORY[i] = ((uint16_t)VGA_COLOR << 8) | ' ';
    }
    cursor_row = 0;
    cursor_col = 0;
}

static void putc(char c) {
    if (c == '\n') {
        cursor_col = 0;
        ++cursor_row;
    } else {
        VGA_MEMORY[cursor_row * VGA_WIDTH + cursor_col] =
            ((uint16_t)VGA_COLOR << 8) | (uint8_t)c;
        ++cursor_col;
        if (cursor_col >= VGA_WIDTH) {
            cursor_col = 0;
            ++cursor_row;
        }
    }

    if (cursor_row >= VGA_HEIGHT) {
        cursor_row = 0;
    }
}

static void puts(const char* text) {
    while (*text != '\0') {
        putc(*text++);
    }
}

static void halt_forever(void) {
    for (;;) {
        __asm__ volatile ("cli; hlt");
    }
}

void kmain(uint32_t multiboot_magic, uint32_t multiboot_info) {
    (void)multiboot_info;

    clear_screen();
    puts("DOVE OS 0.1\n");
    puts("------------------------------\n");
    puts("Kernel booted successfully.\n");
    puts("Multiboot2 entry confirmed.\n");

    if (multiboot_magic == 0x36D76289) {
        puts("Boot protocol: Multiboot2 OK\n");
    } else {
        puts("Boot protocol: INVALID\n");
    }

    puts("\nDOVE kernel foundation online.\n");
    puts("Next: GDT -> IDT -> memory -> processes.\n");

    halt_forever();
}
