format ELF
use32

section ".text"

ISR_ERROR_CODE_NONE equ 0

extrn interrupt_handler

macro ISR_ERROR_STUB l
{
    isr_stub_#l#:
        pushad
        cld
        push l
        call interrupt_handler
        popad
        iret
}
    
macro ISR_NO_ERROR_STUB l
{
    isr_stub_#l#:
        pushad
        cld
        push l
        call interrupt_handler
        popad
        iret
}

ISR_NO_ERROR_STUB   0
ISR_NO_ERROR_STUB   1
ISR_NO_ERROR_STUB   2
ISR_NO_ERROR_STUB   3
ISR_NO_ERROR_STUB   4
ISR_NO_ERROR_STUB   5
ISR_NO_ERROR_STUB   6
ISR_NO_ERROR_STUB   7
ISR_ERROR_STUB      8
ISR_NO_ERROR_STUB   9
ISR_ERROR_STUB      10
ISR_ERROR_STUB      11
ISR_ERROR_STUB      12
ISR_ERROR_STUB      13
ISR_ERROR_STUB      14
ISR_NO_ERROR_STUB   15
ISR_NO_ERROR_STUB   16
ISR_ERROR_STUB      17
ISR_NO_ERROR_STUB   18
ISR_NO_ERROR_STUB   19
ISR_NO_ERROR_STUB   20
ISR_NO_ERROR_STUB   21
ISR_NO_ERROR_STUB   22
ISR_NO_ERROR_STUB   23
ISR_NO_ERROR_STUB   24
ISR_NO_ERROR_STUB   25
ISR_NO_ERROR_STUB   26
ISR_NO_ERROR_STUB   27
ISR_NO_ERROR_STUB   28
ISR_NO_ERROR_STUB   29
ISR_ERROR_STUB      30
ISR_NO_ERROR_STUB   31

public isr_stub_table
isr_stub_table:
    dd isr_stub_0
    dd isr_stub_1
    dd isr_stub_2
    dd isr_stub_3
    dd isr_stub_4
    dd isr_stub_5
    dd isr_stub_6
    dd isr_stub_7
    dd isr_stub_8
    dd isr_stub_9
    dd isr_stub_10
    dd isr_stub_11
    dd isr_stub_12
    dd isr_stub_13
    dd isr_stub_14
    dd isr_stub_15
    dd isr_stub_16
    dd isr_stub_17
    dd isr_stub_18
    dd isr_stub_19
    dd isr_stub_20
    dd isr_stub_21
    dd isr_stub_22
    dd isr_stub_23
    dd isr_stub_24
    dd isr_stub_25
    dd isr_stub_26
    dd isr_stub_27
    dd isr_stub_28
    dd isr_stub_29
    dd isr_stub_30
    dd isr_stub_31
