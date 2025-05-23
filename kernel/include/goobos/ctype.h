#ifndef _CTYPE_H
#define _CTYPE_H

#if __has_builtin(__builtin_isdigit)
#define isdigit(c) __builtin_isdigit(c)
#else
static inline int isdigit(int c)
{
    return '0' <= c && c <= '9';
}
#endif

#endif // _CTYPE_H
