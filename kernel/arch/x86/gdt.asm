format ELF
use32

section ".text"

public gdt_descriptor
gdt_descriptor:
    dw gdt.end - gdt - 1
    dd gdt

gdt:
    dq 0  ; null descriptor

.kernel_code:
    dw 0xFFFF
    dw 0
    db 0
    db 0x9A
    db 0xFC
    db 0

.kernel_data:
    dw 0xFFFF
    dw 0
    db 0
    db 0x92
    db 0xFC
    db 0

.user_code:
    dw 0xFFFF
    dw 0
    db 0
    db 0xFA
    db 0xFC
    db 0

.user_data:
    dw 0xFFFF
    dw 0
    db 0
    db 0xF2
    db 0xFC
    db 0

.end:
