#include <goobos/types.h>
#include <goobos/stddef.h>
#include <goobos/string.h>
#include <video/vga.h>

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
    writer.color = vga_color_code(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    writer.buffer = (struct VGA_Screen_Char *) VGA_BUFFER_OFFSET;
}

void vga_clear_line(size_t line)
{
    for(size_t i = 0; i < VGA_BUFFER_WIDTH; ++i)
    {
        writer.buffer[(line * VGA_BUFFER_WIDTH) + i] = (struct VGA_Screen_Char) {0};
    }
}

void vga_scroll(void)
{
    for(size_t row = 1; row < VGA_BUFFER_HEIGHT; ++row)
    {
        for(size_t col = 0; col < VGA_BUFFER_WIDTH; ++col)
        {
            struct VGA_Screen_Char character = writer.buffer[(row * VGA_BUFFER_WIDTH) + col];
            writer.buffer[((row - 1) * VGA_BUFFER_WIDTH) + col] = character;
        }
    }

    vga_clear_line(VGA_BUFFER_HEIGHT - 1);
}

void vga_newline(void)
{
    vga_scroll();
    writer.cursor_pos = 0;

    /*size_t line = writer.cursor_pos / VGA_BUFFER_WIDTH + 1;*/
    /*writer.cursor_pos = line * VGA_BUFFER_WIDTH;*/
}

void vga_write_byte(u8 c)
{
    if(c == '\n')
    {
        vga_newline();
        return;
    }

    if(writer.cursor_pos >= VGA_BUFFER_WIDTH) vga_newline();

    size_t row = VGA_BUFFER_HEIGHT - 1;

    /*writer.buffer[writer.cursor_pos++] = (struct VGA_Screen_Char) { .character = c, .color = writer.color };*/
    writer.buffer[(row * VGA_BUFFER_WIDTH) + writer.cursor_pos++] = (struct VGA_Screen_Char) { .character = c, .color = writer.color };
}

#define ASCII_PRINTABLE_LOWER_BOUND 0x20
#define ASCII_PRINTABLE_UPPER_BOUND 0x7E
void vga_write_string(const char *s)
{
    for(size_t i = 0; i < strlen(s); ++i)
    {
        if((s[i] >= ASCII_PRINTABLE_LOWER_BOUND && s[i] <= ASCII_PRINTABLE_UPPER_BOUND)
            || s[i] == '\n')
        {
            vga_write_byte(s[i]);
        }
        else vga_write_byte(INVALID_CHARACTER_SYMBOL);
    }
}

void vga_putchar(char c)
{
    if(c >= ASCII_PRINTABLE_LOWER_BOUND && c <= ASCII_PRINTABLE_UPPER_BOUND)
    {
        vga_write_byte(c);
    }
    else if(c == '\n')
    {
        vga_newline();
    }
    else
    {
        vga_write_byte(INVALID_CHARACTER_SYMBOL);
    }
}

void vga_print(const char *s)
{
    vga_write_string(s);
}

void vga_println(const char *s)
{
    vga_write_string(s);
    vga_write_byte('\n');
}
