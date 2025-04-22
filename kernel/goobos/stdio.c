#include <goobos/ctype.h>
#include <goobos/stddef.h>
#include <goobos/stdio.h>
#include <goobos/string.h>
#include <video/vga.h>

#define puts(str) vga_println(str)

#if __has_attribute(__fallthrough__)
# define fallthrough __attribute__((__fallthrough__))
#else
# define fallthrough do {} while(0)
#endif

size_t strnlen(const char *s, size_t count)
{
    const char *sc;

    for(sc = s; count-- && *sc != '\0'; ++sc);

    return sc - s;
}

/* needs to be implemented for weird libgcc related reasons */ 
u64 __udivmoddi4(u64 num, u64 den, u64 *rem_p)
{
    u64 quot = 0, qbit = 1;
    if(den == 0) return 1 / ((unsigned) den); /* intentional divide by zero, without
                                                 triggering a compiler warning which
                                                 would abort the build */

    /* left-justify denominator and count shift */
    while( (s64) den >= 0 )
    {
        den <<= 1;
        qbit <<= 1;
    }

    while( qbit )
    {
        if( den <= num )
        {
            num -= den;
            quot += qbit;
        }
        den >>= 1;
        qbit >>= 1;
    }

    if( rem_p ) *rem_p = num;

    return quot;
}

#define do_div(n, base) \
    ({ \
        unsigned int __base = (base); \
        unsigned int __rem; \
        __rem = ((unsigned long long)(n)) % __base; \
        (n) = ((unsigned long long)(n)) / __base; \
        __rem; \
    })

int atoi(const char *s)
{
    int n = 0;
    char *c = (char *) s;
    while(isdigit(*c))
    {
        n = n * 10 + ((*c)++ - '0');
    }
    return n;
}

#define ZEROPAD 1   /* pad with zero */
#define SIGN    2   /* unsigned/signed long */
#define PLUS    4   /* show plus */
#define SPACE   8   /* space if plus */
#define LEFT    16  /* left justified */
#define SMALL   32  /* must be 32 == 0x20 */
#define SPECIAL 64  /* 0x*/

static char *number(char *str, long num, int base, int size, int precision, int type)
{
    static const char digits[16] = "0123456789ABCDEF";

    char tmp[66];
    char c, sign, locase;
    int i;

    locase = (type & SMALL);
    if(type & LEFT) type &= ~ZEROPAD;
    if(base < 2 || base > 16) return NULL;

    c = (type & ZEROPAD) ? '0' : ' ';
    sign = 0;
    if(type & SIGN)
    {
        if(num < 0)
        {
            sign = '-';
            num = -num;
            --size;
        }
        else if(type & PLUS)
        {
            sign = '+';
            --size;
        }
        else if(type & SPACE)
        {
            sign = ' ';
            --size;
        }
    }
    
    if(type & SPECIAL)
    {
        if(base == 16) size -= 2;
        else if(base == 8) size -= 1;
    }

    i = 0;
    if(num == 0) tmp[i++] = '0';
    else while(num != 0) tmp[i++] = (digits[do_div(num, base)] | locase);

    if(i > precision) precision = i;
    size -= precision;
    
    if(!(type & (ZEROPAD + LEFT)))
    {
        while(size-- > 0) *str++ = ' ';
    }

    if(sign) *str++ = sign;

    if(type & SPECIAL)
    {
        if(base == 8)
        {
            *str++ = '0';
        }
        else if(base == 16)
        {
            *str++ = '0';
            *str++ = ('X' | locase);
        }
    }

    if(!(type & LEFT))
    {
        while(size-- > 0) *str++ = c;
    }

    while(i < precision--) *str++ = '0';
    while(i-- > 0) *str++ = tmp[i];
    while(size-- > 0) *str++ = ' ';

    return str;
}

int vsprintf(char *buf, const char *fmt, va_list args)
{
    int len;
    unsigned long num;
    int i, base;
    char *str;
    const char *s;

    int flags;  /* flags to number() */

    int field_width;    /* width of output field */
    int precision;      /* min. # of digits for integers; max
                           number of chars for from string */
    int qualifier;      /* 'h', 'l', or 'L' for integer fields */

    for(str = buf; *fmt; ++fmt)
    {
        if(*fmt != '%')
        {
            *str++ = *fmt;
            continue;
        }

        /* process flags */
        flags = 0;
    repeat:
        ++fmt;  /* this also skips first '%' */
        switch(*fmt)
        {
        case '-':
            flags |= LEFT;
            goto repeat;
        case '+':
            flags |= PLUS;
            goto repeat;
        case ' ':
            flags |= SPACE;
            goto repeat;
        case '#':
            flags |= SPECIAL;
            goto repeat;
        case '0':
            flags |= ZEROPAD;
            goto repeat;
        }

        /* get field width */
        field_width = -1;
        if(isdigit(*fmt)) field_width = atoi(fmt);
        else if(*fmt == '*')
        {
            ++fmt;
            /* it's the next argument */
            field_width = va_arg(args, int);
            if(field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

        /* get the precision */
        precision = -1;
        if(*fmt == '.')
        {
            ++fmt;
            if(isdigit(*fmt)) precision = atoi(fmt);
            else if(*fmt == '*')
            {
                ++fmt;
                /* it's the next argument */
                precision = va_arg(args, int);
            }
            if(precision < 0) precision = 0;
        }

        /* get the conversion qualifier */
        qualifier = -1;
        if(*fmt == 'h' || *fmt == 'l' || *fmt == 'L')
        {
            qualifier = *fmt;
            ++fmt;
        }

        /* default base */
        base = 10;

        switch(*fmt)
        {
        case 'c':
            if(!(flags & LEFT))
            {
                while(--field_width > 0) *str++ = ' ';
            }
            *str++ = (unsigned char) va_arg(args, int);
            while(--field_width > 0) *str++ = ' ';
            continue;

        case 's':
            s = va_arg(args, char *);
            len = strnlen(s, precision);

            if(!(flags & LEFT))
            {
                while(len < field_width--) *str++ = ' ';
            }
            for(i = 0; i < len; ++i) *str++ = *s++;
            while(len < field_width--) *str++ = ' ';
            continue;

        case 'p':
            if(field_width == -1)
            {
                field_width = 2 * sizeof(void *);
                flags |= ZEROPAD;
            }
            str = number(str, (unsigned long) va_arg(args, void *), 16, field_width, precision, flags);
            continue;

        case 'n':
            if(qualifier == -1)
            {
                long *ip = va_arg(args, long *);
                *ip = (str - buf);
            }
            else
            {
                int *ip = va_arg(args, int *);
                *ip = (str - buf);
            }
            continue;

        case '%':
            *str++ = '%';
            continue;

            /* integer number formats - set up the flags and "break" */
        case 'o':
            base = 8;
            break;

        case 'x':
            flags |= SMALL;
            fallthrough;

        case 'X':
            base = 16;
            break;

        case 'd':
        case 'i':
            flags |= SIGN;
            break;

        case 'u':
            break;

        default:
            *str++ = '%';
            if(*fmt) *str++ = *fmt;
            else --fmt;
            continue;
        }

        if(qualifier == 'l') num = va_arg(args, unsigned long);
        else if(qualifier == 'h')
        {
            num = (unsigned short) va_arg(args, int);
            if(flags & SIGN) num = (short) num;
        }
        else if(flags & SIGN) num = va_arg(args, int);
        else num = va_arg(args, unsigned int);
        str = number(str, num, base, field_width, precision, flags);
    }

    *str = '\0';
    return str - buf;
}

int sprintf(char *buf, const char *fmt, ...)
{
    va_list args;
    int i;

    va_start(args, fmt);
    i = vsprintf(buf, fmt, args);
    va_end(args);
    return i;
}

int printf(const char *fmt, ...)
{
    char printf_buf[1024];
    va_list args;
    int printed;

    va_start(args, fmt);
    printed = vsprintf(printf_buf, fmt, args);
    va_end(args);

    puts(printf_buf);

    return printed;
}
