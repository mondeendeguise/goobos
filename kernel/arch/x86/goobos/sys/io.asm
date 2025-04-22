format ELF
use32

section ".text"

public inb
inb:
    ; cdecl calling convention
    pop dx
    in al, dx
    ret

public outb
outb:
    pop dx
    pop ax
    out dx, al
    ret
