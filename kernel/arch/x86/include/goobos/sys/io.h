#ifndef X86_GOOBOS_SYS_IO_H_
#define X86_GOOBOS_SYS_IO_H_

#include <goobos/types.h>

extern u8 inb(u16 port);
extern void outb(u8 value, u16 port);

#endif // X86_GOOBOS_SYS_IO_H_
