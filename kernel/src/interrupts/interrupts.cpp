#include "interrupts.h"
#include "../panic.h"
#include "../portIO.h"

extern Graphics* graphics;

__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame* frame){
    SysPanic("Page Fault Detected");
    while(true);
}

__attribute__((interrupt)) void DoubleFault_Handler(struct interrupt_frame* frame){
    SysPanic("Double Fault Detected");
    while(true);
}

__attribute__((interrupt)) void GPFault_Handler(struct interrupt_frame* frame){
    SysPanic("General Protection Fault Detected");
    while(true);
}

__attribute__((interrupt)) void KeyboardInt_Handler(struct interrupt_frame* frame){
    graphics->print(0, "Pressed", 0, 0);
    uint8_t scancode = inb(0x60);
    PIC_EndMaster();
}

void PIC_EndMaster(){
    outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_EndSlave(){
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}
   

void RemapPIC(){
    uint8_t a1, a2; 

    a1 = inb(PIC1_DATA);
    io_wait();
    a2 = inb(PIC2_DATA);
    io_wait();

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, 0x20);
    io_wait();
    outb(PIC2_DATA, 0x28);
    io_wait();

    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);

}