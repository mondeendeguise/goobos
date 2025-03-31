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

CFLAGS ?= -Wall -Wextra -pedantic -O2 -ggdb

OBJS := $(ARCH_DIR)/multiboot.o \
		$(ARCH_DIR)/boot.o \
		$(ARCH_DIR)/gdt.o \
		$(ARCH_DIR)/idt_32.o \
		$(ARCH_DIR)/interrupts.o \
		$(SRC_DIR)/kernel.o

INCLUDES := -I./include -I$(ARCH_DIR)/include

CFLAGS += -nostdlib -nostdinc -fno-common -fno-builtin -ffreestanding $(INCLUDES)

.PHONY: all clean install uninstall

all: $(KERNEL)

$(KERNEL): $(OBJS) $(LD_SCRIPT)
	$(CC) -T $(LD_SCRIPT) -o $@ -ffreestanding -nostdlib $(OBJS)
	grub-file --is-x86-multiboot2 $@

$(ARCH_DIR)/%.o: $(ARCH_DIR)/%.asm
	$(FASM) $< $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
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
