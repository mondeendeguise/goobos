#include <idt_32.h>
#include <goobos/types.h>

#define IDT_MAX_DESCRIPTORS 256
#define KERNEL_CODE_SEGMENT 0x8

struct __attribute__((packed)) idt_entry
{
    u16 isr_low;
    u16 segment_selector;
    u8 reserved;
    u8 attributes;
    u16 isr_high;
};

struct __attribute__((packed)) idt_descriptor
{
    u16 size;
    u32 offset;
};

__attribute__((aligned(0x10)))
static struct idt_entry idt[IDT_MAX_DESCRIPTORS];

struct idt_descriptor idt_descriptor;

void idt_set_descriptor(u8 vector, void *isr, u8 flags)
{
    struct idt_entry *descriptor = &idt[vector];

    descriptor->isr_low = (u16) ((u32) isr & 0xFFFF);
    descriptor->segment_selector = KERNEL_CODE_SEGMENT;
    descriptor->reserved = 0;
    descriptor->attributes = flags;
    descriptor->isr_high = (u16) ((u32) isr >> 16);
}

extern void *overflow_exception_handler;

void idt_init(void)
{
    idt_descriptor.size = sizeof(struct idt_entry) * IDT_MAX_DESCRIPTORS - 1;
    idt_descriptor.offset = (u32) idt;

    idt_set_descriptor(4, overflow_exception_handler, 0x8E);
}
