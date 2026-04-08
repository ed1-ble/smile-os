NAME = smile-os
PREFIX = $(HOME)/cross-compiler/cross
TARGET = i686-elf
export PATH := $(PREFIX)/bin:$(PATH)

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

all: $(NAME).iso

$(NAME).iso: ../isodir/boot/$(NAME)
	grub2-mkrescue -o $(NAME).iso ../isodir

../isodir/boot/$(NAME): $(NAME)
	cp $(NAME) ../isodir/boot/$(NAME)
	mkdir -p ../isodir/boot

$(NAME): kernel.o boot.o vga.o gdt.o gdts.o util.o idt.o idts.o timer.o stdio.o keyboard.o linker.ld
	$(TARGET)-gcc -T linker.ld -o $(NAME) -ffreestanding -O2 -nostdlib kernel.o boot.o vga.o gdt.o gdts.o util.o idt.o idts.o timer.o stdio.o keyboard.o -lgcc


keyboard.o: keyboard.c
	$(TARGET)-gcc -c keyboard.c -o keyboard.o $(CFLAGS)
stdio.o: stdio.c
	$(TARGET)-gcc -c stdio.c -o stdio.o $(CFLAGS)
timer.o: timer.c
	$(TARGET)-gcc -c timer.c -o timer.o $(CLFAGS)
idt.o: idt.c
	$(TARGET)-gcc -c idt.c -o idt.o $(CFLAGS)
util.o: util.c
	$(TARGET)-gcc -c util.c -o util.o $(CFLAGS)
gdt.o: gdt.c
	$(TARGET)-gcc -c gdt.c -o gdt.o $(CFLAGS)
kernel.o: kernel.c 
	$(TARGET)-gcc -c kernel.c -o kernel.o $(CFLAGS)
vga.o: vga.c
	$(TARGET)-gcc -c vga.c -o vga.o $(CFLAGS)

idts.o: idt.s
	nasm -f elf32 idt.s -o idts.o
gdts.o: gdt.s
	nasm -f elf32 gdt.s -o gdts.o
boot.o: boot.s
	$(TARGET)-as boot.s -o boot.o

.PHONY: clean
clean:
	rm -f *.o $(NAME) $(NAME).iso
	rm -f ../isodir/boot/$(NAME)
