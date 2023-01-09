#pragma once
#include "BitOSDatatypes.h"
#include "PageFrameAllocator.h"
//#include "math.h"
#include "renderWindow.h"
#include "efiMemory.h"
#include "gdt/gdt.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupts.h"
#include "portIO.h"

extern uint64_t screenWidth;
extern uint64_t screenHeight;
extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;


uint64_t screenWidth;
uint64_t screenHeight;

IDTR idtr;
void PrepareInterrupts(){
    idtr.Limit = 0x0FFF;
    idtr.Offset = (uint64_t)GlobalAllocator.RequestPage();

    IDTDescEntry* int_PageFault = (IDTDescEntry*)(idtr.Offset + 0xE * sizeof(IDTDescEntry));
    int_PageFault->SetOffset((uint64_t)PageFault_Handler);
    int_PageFault->type_attr = IDT_TA_InterruptGate;
    int_PageFault->selector = 0x08;

    IDTDescEntry* int_DoubleFault = (IDTDescEntry*)(idtr.Offset + 0x8 * sizeof(IDTDescEntry));
    int_DoubleFault->SetOffset((uint64_t)DoubleFault_Handler);
    int_DoubleFault->type_attr = IDT_TA_InterruptGate;
    int_DoubleFault->selector = 0x08;

    IDTDescEntry* int_GPFault = (IDTDescEntry*)(idtr.Offset + 0xD * sizeof(IDTDescEntry));
    int_GPFault->SetOffset((uint64_t)GPFault_Handler);
    int_GPFault->type_attr = IDT_TA_InterruptGate;
    int_GPFault->selector = 0x08;

    IDTDescEntry* int_Keyboard = (IDTDescEntry*)(idtr.Offset + 0x21 * sizeof(IDTDescEntry));
    int_Keyboard->SetOffset((uint64_t)KeyboardInt_Handler);
    int_Keyboard->type_attr = IDT_TA_InterruptGate;
    int_Keyboard->selector = 0x08;

    asm ("lidt %0" : : "m" (idtr));

    RemapPIC();

    outb(PIC1_DATA, 0b11111101);
    outb(PIC2_DATA, 0b11111111);

    asm ("sti");

}

void bootHelper(BootInfo* bootInfo){

    screenWidth = bootInfo->framebuffer->Width;
    screenHeight = bootInfo->framebuffer->Height;
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;
    GlobalAllocator = PageFrameAllocator();
    GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1 + 5; //add 5 just in case
    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize+0x1000;
    GlobalAllocator.LockPages((void*)fbBase, fbSize / 0x1000 + 1);

    GDTDescriptor gdtDescriptor;
    gdtDescriptor.Size = sizeof(GDT) - 1;
    gdtDescriptor.Offset = (uint64_t)&DefaultGDT;
    LoadGDT(&gdtDescriptor);

    //memset(bootInfo->framebuffer->BaseAddress, 123, bootInfo->framebuffer->BufferSize);

    PrepareInterrupts();
}
