global idt_flush
idt_flush:
    ; esp + 4 = idt_ptr 
    MOV eax, [esp+4]
    LIDT [eax] ; load idt_ptr into the IDT register
    STI ; start responding to hardware interupts
    RET

; two kinds of Interupt Service Routine (ISR) <- a function triggered when interupt
; 1st -> Has err code
; 2nd -> No err code

%macro ISR_NOERRCODE 1
    global isr%1
    isr%1:
        CLI ; turn off / clear interrupts
        PUSH LONG 0
        PUSH LONG %1
        JMP isr_common_stub ; common set of code to handle interrupts
%endmacro

%macro ISR_ERRCODE 1
    global isr%1
    isr%1:
        CLI
        PUSH LONG %1
        JMP isr_common_stub
%endmacro

%macro IRQ 2
    global irq%1
    irq%1:
        CLI
        PUSH LONG 0
        PUSH LONG %2
        JMP irq_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7

ISR_ERRCODE 8
ISR_NOERRCODE 9 
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 128
ISR_NOERRCODE 177

IRQ 0, 32
IRQ   1,    33
IRQ   2,    34
IRQ   3,    35
IRQ   4,    36
IRQ   5,    37
IRQ   6,    38
IRQ   7,    39
IRQ   8,    40
IRQ   9,    41
IRQ  10,    42
IRQ  11,    43
IRQ  12,    44
IRQ  13,    45
IRQ  14,    46
IRQ  15,    47

extern isr_handler
isr_common_stub: 
; 1. Pushes values in relevant registers to stack (ie. FREEZE the current state)
; 2. Calls isr_handler to handle the Interrupt with the address of registers as argument

    PUSHA ; Push all general purpose regs
    MOV eax, ds ; Saves Data Segment selector, tells OS what memory previous program was using
    PUSH eax
    MOV eax, cr2 ; CR2 <- special Control Register, holds memory addr that caused Page Fault
    PUSH eax

    MOV ax, 0x10
    MOV ds, ax 
    MOV es, ax
    MOV fs, ax
    MOV gs, ax ; Offset Segment Registers by 0x10, looks at OS memory instead of User program memory

    PUSH esp ; Push a pointer to all saved regs as one arg to isr_handler function
    CALL isr_handler 

    ADD esp, 8 ; Cleans PUSH esp & PUSH eax, cr2
    POP ebx 
    MOV ds, bx
    MOV es, bx
    MOV fs, bx
    MOV gs, bx ; Restore orig data segments

    POPA ; Restore general purpose regs
    ADD esp, 8 ; Removes Interrupts Num, Err code
    STI 
    IRET

extern irq_handler
irq_common_stub: 

    PUSHA 
    MOV eax, ds 
    PUSH eax
    MOV eax, cr2 
    PUSH eax

    MOV ax, 0x10
    MOV ds, ax 
    MOV es, ax
    MOV fs, ax
    MOV gs, ax 

    PUSH esp 
    CALL irq_handler 

    ADD esp, 8 
    POP ebx 
    MOV ds, bx
    MOV es, bx
    MOV fs, bx
    MOV gs, bx 

    POPA 
    ADD esp, 8 
    STI 
    IRET
