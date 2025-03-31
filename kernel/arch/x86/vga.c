#include <goobos/types.h>
#include <goobos/stddef.h>
#include <goobos/string.h>
#include <vga.h>

VGA_Color_Code vga_color_code(enum VGA_Color fg, enum VGA_Color bg)
{
    return ((bg & 0xF) << 4) | (fg & 0xF);
}

struct VGA_Screen_Char
{
    u8 character;
    VGA_Color_Code color;
};

struct VGA_Writer
{
    size_t cursor_pos;
    VGA_Color_Code color;
    struct VGA_Screen_Char *buffer;
};

static struct VGA_Writer writer = {0};

void vga_init(void)
{
    writer.cursor_pos = 0;
    writer.color = vga_color_code(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    writer.buffer = (struct VGA_Screen_Char *) VGA_BUFFER_OFFSET;
}

void vga_newline(void)
{
    size_t line = writer.cursor_pos / VGA_BUFFER_WIDTH + 1;
    writer.cursor_pos = line * VGA_BUFFER_WIDTH;
}

void vga_write_byte(u8 c)
{
    if(c == '\n')
    {
        vga_newline();
        return;
    }

    writer.buffer[writer.cursor_pos++] = (struct VGA_Screen_Char) { .character = c, .color = writer.color };
}

void vga_write_string(const char *s)
{
    for(size_t i = 0; i < strlen(s); ++i)
    {
        vga_write_byte(s[i]);
    }
}
