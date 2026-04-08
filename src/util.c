#include <stdint.h>
#include "util.h"

void memset(void* dest, char val, uint32_t count)
{
    char* temp = (char*) dest;
    for (; count != 0; count--) 
    {
        *temp++ = val;
    }
}

void outPortB(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
    // outputs a byte of data to specified I/O port
    // this one is hooked up to PIC, so we send data directly to the chips
    //
    // value => for init of the chips, so we can create the IDT
}

char inPortB(uint16_t port)
{
    char rv;
    asm volatile("inb %1, %0": "=a"(rv):"dN"(port));
    return rv;
}
