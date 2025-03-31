#include <goobos/types.h>
#include <vga.h>

void stack_overflow(void)
{
    stack_overflow();
}

void kernel_main(void)
{
    vga_init();

    vga_write_string("Hello, world!\n");
    vga_write_string("Newline\n");

    while(1);
}
