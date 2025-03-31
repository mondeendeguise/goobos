include toolchain.mk

ARCH ?= x86_64
VERSION := 2025.03.29

SYSROOT := $(abspath ./sysroot)
ISO_DIR := $(abspath ./isodir)
ISO_FILE := $(abspath ./goobos-$(VERSION)-$(ARCH).iso)

PREFIX ?= $(SYSROOT)

# export CFLAGS = -m32 -nostdlib -nostdinc -fno-common -fno-builtin -ffreestanding --sysroot=$(PREFIX) -isystem $(PREFIX)/usr/include

.PHONY: all iso kernel clean

all: iso

iso: $(ISO_FILE)

$(ISO_FILE): PREFIX := $(ISO_DIR)
$(ISO_FILE): install-kernel
	mkdir -p $(ISO_DIR)/boot/grub
	cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue $(ISO_DIR) -o $@

kernel:
	$(MAKE) -C kernel

install-kernel:
	$(MAKE) -C kernel PREFIX=$(PREFIX) install

clean:
	rm -f $(ISO_FILE)
	$(MAKE) -C kernel clean
	rm -rf $(ISO_DIR)
	rm -rf $(SYSROOT)
