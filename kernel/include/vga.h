#ifndef VGA_H_
#define VGA_H_

#include <goobos/types.h>
#include <goobos/stddef.h>

#define VGA_BUFFER_HEIGHT 25
#define VGA_BUFFER_WIDTH 80

#define VGA_BUFFER_OFFSET 0xB8000

void vga_init(void);

void vga_write_byte(u8 c);
void vga_write_string(const char *s);

enum VGA_Color
{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_PINK = 13,
    VGA_COLOR_YELLOW = 14,
    VGA_COLOR_WHITE = 15,
};

typedef u8 VGA_Color_Code;

VGA_Color_Code vga_color_code(enum VGA_Color fg, enum VGA_Color bg);

#endif // VGA_H_
