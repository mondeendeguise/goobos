format ELF
use32

section ".init"

public _init
_init:
    push ebp
    mov ebp, esp

section ".fini"

public _fini
_fini:
    push ebp
    mov ebp, esp
