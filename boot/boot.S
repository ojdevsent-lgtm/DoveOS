/* DOVE OS - Multiboot2 entry point */
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0xE85250D6
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 8
.long MAGIC
.long 0
.long 16
.long CHECKSUM

/* End tag */
.long 0
.long 0

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    cli
    mov $stack_top, %esp

    /* Multiboot2 passes magic in EAX and information pointer in EBX. */
    push %ebx
    push %eax
    call kmain

1:
    cli
    hlt
    jmp 1b
.size _start, .-_start
