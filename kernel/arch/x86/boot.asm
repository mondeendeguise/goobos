format ELF
use32

section ".text"

extrn idt_create
extrn vga_init

extrn _init
extrn kernel_main

public _start
_start:

    cli

    call check_multiboot
    call gdt_init

    mov esp, stack_top

    call idt_init
    call vga_init
    sti

    call _init
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



extrn gdt_descriptor
gdt_init:
    lgdt [gdt_descriptor]
    jmp 0x08:.reload_cs ; code segment

.reload_cs:
    mov ax, 0x10  ; data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret



extrn idt_descriptor
idt_init:
    call idt_create
    lidt [idt_descriptor]
    ret



error:
    cli
    mov dword [0xb8000], 0x4F524F45
    mov dword [0xb8004], 0x4F3A4F52
    mov dword [0xb8008], 0x4F204F20
    mov byte [0xb800A], al
    jmp panic



panic:
    hlt
    jmp panic



section ".bss" align 16

define STACK_SIZE 0x4000  ; 16 KiB
stack_bottom:
    rb STACK_SIZE
stack_top:
