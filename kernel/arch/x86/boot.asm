format ELF
use32

section ".text"

extrn gdt_descriptor
extrn idt_descriptor

;extrn _init
extrn idt_init
extrn kernel_main

public _start
_start:

    call check_multiboot
    call idt_init

    cli
    lgdt [gdt_descriptor]
    lidt [idt_descriptor]

    mov esp, stack_top

    ;call _init

    call kernel_main

    jmp panic

_start_size = $ - _start

define MULTIBOOT_STATE_MAGIC 0x36D76289

check_multiboot:
    cmp eax, MULTIBOOT_STATE_MAGIC
    jne .no_multiboot
    ret

.no_multiboot:
    mov al, "M"
    jmp error

error:
    mov dword [0xb8000], 0x4F524F45
    mov dword [0xb8004], 0x4F3A4F52
    mov dword [0xb8008], 0x4F204F20
    mov byte [0xb800A], al
    jmp panic

panic:
    cli
    hlt
    jmp $

section ".bss" align 16

define STACK_SIZE 0x4000  ; 16 KiB

stack_bottom:
    rb STACK_SIZE
stack_top:

