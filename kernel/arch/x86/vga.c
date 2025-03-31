#include <vga.h>

VGA_Color_Code vga_color_code(enum VGA_Color fg, enum VGA_Color bg)
{
    VGA_Color_Code ret = 0;
    ret |= fg & 0xF;
    ret |= (bg & 0xF) << 4;
    return ret;
}

