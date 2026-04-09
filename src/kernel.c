#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "stdio.h"
#include "keyboard.h"
#include "shell.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, dingus."
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler!!"
#endif

#define BANNER " ____            _ _         ___  ____  \n/ ___| _ __ ___ (_) | ___   / _ \\/ ___| \n\\___ \\| '_ ` _ \\| | |/ _ \\ | | | \\___ \\ \n ___) | | | | | | | |  __/ | |_| |___) |\n|____/|_| |_| |_|_|_|\\___|  \\___/|____/ \n"

void kernel_main(void)
{
    reset_screen();
    print("BOOTING...\n\n");   

    initGdt();
    print_color("[OK] GDT INITIALIZED\n", VGA_COLOR_GREEN);
    
    initIdt();
    print_color("[OK] IDT INITIALIZED\n", VGA_COLOR_GREEN);

    initTimer();
    print_color("[OK] TIMER INITIALIZED\n", VGA_COLOR_GREEN);

    initKeyboard();
    print_color("[OK] KEYBOARD INITIALIZED\n", VGA_COLOR_GREEN);

    reset_screen();

    print_color(BANNER, VGA_COLOR_LIGHT_RED);
    
    print_prompt();
    for (;;);
}
