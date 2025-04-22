KERNEL ?= kernel.bin
ARCH ?= x86_64
PREFIX ?= ../sysroot

SRCARCH := $(ARCH)

ifeq ($(ARCH),i386)
	SRCARCH := x86
endif
ifeq ($(ARCH),x86_64)
	SRCARCH := x86
endif

ARCH_DIR := arch/$(SRCARCH)
SRC_DIR := src

LD_SCRIPT := $(ARCH_DIR)/kernel.ld

KERNEL_OBJS := $(ARCH_DIR)/multiboot.o \
				$(ARCH_DIR)/boot.o \
				$(ARCH_DIR)/gdt.o \
				$(ARCH_DIR)/idt/idt.o \
				$(ARCH_DIR)/idt/idt_32.o \
				$(ARCH_DIR)/idt/interrupts.o \
				$(ARCH_DIR)/idt/isr.o \
				$(ARCH_DIR)/goobos/sys/io.o \
				goobos/string.o \
				goobos/stdio.o \
				$(SRC_DIR)/video/vga.o \
				$(SRC_DIR)/kernel.o

OBJS := $(ARCH_DIR)/crti.o \
		$(ARCH_DIR)/crtbegin.o \
		$(KERNEL_OBJS) \
		$(ARCH_DIR)/crtend.o \
		$(ARCH_DIR)/crtn.o

INCLUDES := -I./include -I$(ARCH_DIR)/include

CFLAGS ?= -Wall -Wextra -pedantic -O2 -ggdb

CFLAGS += -nostdlib -nostdinc -fno-common -fno-builtin -ffreestanding $(INCLUDES)

.PHONY: all clean install uninstall

all: $(KERNEL)

$(KERNEL): $(OBJS) $(LD_SCRIPT)
	$(LD) -T $(LD_SCRIPT) -o $@ -nostdlib $(OBJS)
	grub-file --is-x86-multiboot2 $@

# $(ARCH_DIR)/idt/handlers/%.o: $(ARCH_DIR)/idt/handlers/%.c
# 	$(CC) $(CFLAGS) -mgeneral-regs-only -MD -c $< -o $@

$(ARCH_DIR)/%.o: $(ARCH_DIR)/%.asm
	$(FASM) $< $@

$(ARCH_DIR)/%.o: $(ARCH_DIR)/%.c
	$(CC) $(CFLAGS) -MD -c $< -o $@

$(ARCH_DIR)/crtbegin.o $(ARCH_DIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MD -c $< -o $@

goobos/%.o: goobos/%.c
	$(CC) $(CFLAGS) -MD -c $< -o $@

clean:
	rm -f $(KERNEL)
	rm -f $(OBJS)
	rm -f $(OBJS:.o=.d)

install: $(KERNEL)
	mkdir -p $(PREFIX)/boot/
	cp $< $(PREFIX)/boot/

uninstall:
	rm -f $(PREFIX)/boot/$(KERNEL)
