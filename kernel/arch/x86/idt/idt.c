#include <idt/idt.h>

struct IDT_Entry idt[IDT_MAX_DESCRIPTORS] __attribute__((aligned(0x10)));
