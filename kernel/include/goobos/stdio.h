#ifndef GOOBOS_STDIO_H_
#define GOOBOS_STDIO_H_

#include <goobos/stdarg.h>

int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char *buf, const char *fmt, ...);
int printf(const char *fmt, ...);

#endif // GOOBOS_STDIO_H_
