#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "stdio.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, dingus."
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler!!"
#endif

void kernel_main(void)
{
    initGdt();
    initIdt();
    reset_screen();
    print("Smile OS 2.0\n");
    print("Hello there\nYessir\n");
    print_color("GDT success\n", VGA_COLOR_RED);
    print_color("IDT success\n", VGA_COLOR_BLUE);
    int n = 1;
    char c = 'a';
    printf("Number n: %d, Char c: %c",n,c);
}
