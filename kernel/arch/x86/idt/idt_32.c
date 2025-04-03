#include <idt/idt_32.h>
#include <idt/idt.h>
#include <idt/interrupts.h>
#include <goobos/types.h>

struct IDT_Descriptor idt_descriptor;

void idt_set_descriptor(u8 vector, void *isr, u8 flags)
{
    struct IDT_Entry *descriptor = &idt[vector];

    descriptor->isr_low = (u16) ((u32) isr & 0xFFFF);
    descriptor->segment_selector = KERNEL_CODE_SEGMENT;
    descriptor->reserved = 0;
    descriptor->attributes = flags;
    descriptor->isr_high = (u16) ((u32) isr >> 16);
}

static bool vectors[IDT_MAX_DESCRIPTORS];
extern void *isr_stub_table[];

void idt_create(void)
{
    idt_descriptor.size = sizeof(struct IDT_Entry) * IDT_MAX_DESCRIPTORS - 1;
    idt_descriptor.offset = (u32) idt;

    for(u8 vector = 0; vector < EXCEPTION_VECTOR_MAX; ++vector)
    {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }
}
