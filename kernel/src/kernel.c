#include <goobos/types.h>
#include <vga.h>

void stack_overflow(void)
{
    stack_overflow();
}

void kernel_main(void)
{
    vga_init();

    vga_println("Hello, world!");
    vga_println("Newline");

    vga_scroll(5);

    vga_println("Hey hey!");

    while(1);
}
