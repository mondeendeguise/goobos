format ELF
use32

define MAGIC 0xE85250D6
define ARCHITECTURE 0 ; 0 = 32-bit protected mode .. 4 = 32-bit MIPS
HEADER_LENGTH = header_end - header_start
CHECKSUM = -(MAGIC + ARCHITECTURE + HEADER_LENGTH)

section ".multiboot" align 8

header_start:
    dd MAGIC
    dd ARCHITECTURE
    dd HEADER_LENGTH
    dd CHECKSUM

.flags:
    dw 0
    dw 0
    dd 8

header_end:
