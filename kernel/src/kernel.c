#include <goobos/types.h>
#include <vga.h>

extern void load_page_directory(unsigned int *);
extern void enable_paging(void);

u32 page_directory[1024] __attribute__((aligned(4096)));
u32 first_page_table[1024] __attribute__((aligned(4096)));

void stack_overflow(void)
{
    stack_overflow();
}

void kernel_main(void)
{
    for(int i = 0; i < 1024; ++i)
    {
        page_directory[i] = 0x00000002;
    }

    for(unsigned int i = 0; i < 1024; ++i)
    {
        first_page_table[i] = (i * 0x1000) | 3; // attributes: supervisor level, read/write, present
    }

    page_directory[0] = ((unsigned int) first_page_table) | 3;

    stack_overflow();

    /*load_page_directory(page_directory);*/
    /*enable_paging();*/

    while(1);
}
