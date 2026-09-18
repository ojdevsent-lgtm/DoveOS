#include "../../include/types.h"
#include "idt.h"

struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t always_zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct idt_entry idt[256];
static struct idt_ptr idtp;

extern void idt_load(uint32_t address);
extern void isr_default(void);

static void idt_set_gate(uint8_t index, uint32_t base, uint16_t selector, uint8_t flags) {
    idt[index].base_low = (uint16_t)(base & 0xFFFF);
    idt[index].base_high = (uint16_t)((base >> 16) & 0xFFFF);
    idt[index].selector = selector;
    idt[index].always_zero = 0;
    idt[index].flags = flags;
}

void idt_init(void) {
    idtp.limit = (uint16_t)(sizeof(idt) - 1);
    idtp.base = (uint32_t)&idt;

    for (uint16_t i = 0; i < 256; ++i) {
        idt_set_gate((uint8_t)i, (uint32_t)isr_default, 0x08, 0x8E);
    }

    idt_load((uint32_t)&idtp);
}
