#ifndef IDT_IDT_H_
#define IDT_IDT_H_

#include <idt/interrupts.h>

#define IDT_MAX_DESCRIPTORS 256

#ifdef ARCH_X86_64
#include <idt/idt_64.h>
#else
#include <idt/idt_32.h>
#endif

void idt_create(void);

/*struct __attribute__((packed)) IDT*/
/*{*/
/*    union {*/
/*        struct {*/
/*            struct IDT_Entry division_error;*/
/*            struct IDT_Entry debug;*/
/*            struct IDT_Entry non_maskable_interrupt;*/
/*            struct IDT_Entry breakpoint;*/
/*            struct IDT_Entry overflow;*/
/*            struct IDT_Entry bound_range_exceeded;*/
/*            struct IDT_Entry invalid_opcode;*/
/*            struct IDT_Entry device_not_available;*/
/*            struct IDT_Entry double_fault;*/
/**/
/*            struct IDT_Entry _coprocessor_segment_overrun;  // unused*/
/**/
/*            struct IDT_Entry invalid_tss;*/
/*            struct IDT_Entry segment_not_present;*/
/*            struct IDT_Entry stack_segment_fault;*/
/*            struct IDT_Entry general_protection_fault;*/
/*            struct IDT_Entry page_fault;*/
/**/
/*            struct IDT_Entry reserved_1;*/
/**/
/*            struct IDT_Entry x87_floating_point_exception;*/
/*            struct IDT_Entry alignment_check;*/
/*            struct IDT_Entry machine_check;*/
/*            struct IDT_Entry simd_floating_point_exception;*/
/*            struct IDT_Entry virtualization_exception;*/
/*            struct IDT_Entry control_protection_exception;*/
/**/
/*            struct IDT_Entry reserved_2[5];*/
/**/
/*            struct IDT_Entry hypervisor_injection_exception;*/
/*            struct IDT_Entry vmm_communicator_exception;*/
/*            struct IDT_Entry security_exception;*/
/**/
/*            struct IDT_Entry reserved_3;*/
/*        } name;*/
/**/
/*        struct IDT_Entry arr[EXCEPTION_VECTOR_MAX];*/
/*    };*/
/*};*/

/*extern struct IDT idt;*/
extern struct IDT_Entry idt[IDT_MAX_DESCRIPTORS];

#endif // IDT_IDT_H_
