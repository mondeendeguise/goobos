#include <goobos/types.h>
#include <goobos/stdio.h>
#include <idt/idt.h>

void kernel_main(void)
{
    printf("Hello, world! %d", 11);

    asm volatile ("int3");

    // TODO: halt
    while(1);
}
