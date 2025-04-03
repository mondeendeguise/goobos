#ifndef IDT_IDT_32_H_
#define IDT_IDT_32_H_

#include <goobos/types.h>

struct __attribute__((packed)) IDT_Entry
{
    u16 isr_low;
    u16 segment_selector;
    u8 reserved;
    u8 attributes;
    u16 isr_high;
};

struct __attribute__((packed)) IDT_Descriptor
{
    u16 size;
    u32 offset;
};

void idt_set_descriptor(u8 vector, void *isr, u8 flags);

#endif // IDT_IDT_32_H_
