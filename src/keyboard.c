#include "stdint.h"
#include "util.h"
#include "idt.h"
#include "stdio.h"
#include "keyboard.h"

void keyboardHandler(struct InterruptRegisters *regs)
{
    char scanCode = inPortB(0x60) & 0x7F; // Code for key
    char press = inPortB(0x60) & 0x80; // Pressed down or released
    printf("Scan: %d, Pressed: %d\n", scanCode, press);
}

void initKeyboard()
{
    irq_install_handler(1, &keyboardHandler);
}
