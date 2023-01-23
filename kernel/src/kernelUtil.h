#pragma once
#include "BitOSDatatypes.h"
#include "PageFrameAllocator.h"
#include "mouse/mouse.h"
#include "renderWindow.h"
#include "efiMemory.h"
#include "gdt/gdt.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupts.h"
#include "portIO.h"
#include "keyboard/KeyPressType.h"

extern uint64_t screenWidth;
extern uint64_t screenHeight;
extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

uint64_t screenWidth;
uint64_t screenHeight;

IDTR idtr;
void SetIDTGate(void *handler, uint8_t entryOffset, uint8_t type_attr, uint8_t selector)
{

    IDTDescEntry *interrupt = (IDTDescEntry *)(idtr.Offset + entryOffset * sizeof(IDTDescEntry));
    interrupt->SetOffset((uint64_t)handler);
    interrupt->type_attr = type_attr;
    interrupt->selector = selector;
}

void PrepareInterrupts()
{
    idtr.Limit = 0x0FFF;
    idtr.Offset = (uint64_t)GlobalAllocator.RequestPage();

    SetIDTGate((void *)PageFault_Handler, 0xE, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void *)DoubleFault_Handler, 0x8, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void *)GPFault_Handler, 0xD, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void *)KeyboardInt_Handler, 0x21, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void *)MouseInt_Handler, 0x2C, IDT_TA_InterruptGate, 0x08);

    asm("lidt %0"
        :
        : "m"(idtr));

    RemapPIC();
}

void bootHelper(BootInfo *bootInfo)
{
    screenWidth = bootInfo->framebuffer->Width;
    screenHeight = bootInfo->framebuffer->Height;
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;
    GlobalAllocator = PageFrameAllocator();
    GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1 + 5; // add 5 just in case
    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
    GlobalAllocator.LockPages((void *)fbBase, fbSize / 0x1000 + 1);

    GDTDescriptor gdtDescriptor;
    gdtDescriptor.Size = sizeof(GDT) - 1;
    gdtDescriptor.Offset = (uint64_t)&DefaultGDT;
    LoadGDT(&gdtDescriptor);

    memset(bootInfo->framebuffer->BaseAddress, 1, bootInfo->framebuffer->BufferSize);

    PrepareInterrupts();

    InitPS2Mouse();

    outb(PIC1_DATA, 0b11111001);
    outb(PIC2_DATA, 0b11101111);

    asm("sti");
}
