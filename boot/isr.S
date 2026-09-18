.section .text
.global isr_default
.type isr_default, @function
isr_default:
    cli
1:
    hlt
    jmp 1b
.size isr_default, .-isr_default
