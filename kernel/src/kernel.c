#include <goobos/types.h>
#include <vga.h>
#include <idt/idt.h>

void kernel_main(void)
{
    vga_println("Hello, world!");

    // TODO: halt
    while(1);
}
