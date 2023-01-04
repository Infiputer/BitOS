#pragma once
#include "BitOSDatatypes.h"
#include "PageFrameAllocator.h"


extern uint64_t screenWidth;
extern uint64_t screenHeight;
extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;


uint64_t screenWidth;
uint64_t screenHeight;
 

void bootHelper(BootInfo* bootInfo){

    screenWidth = bootInfo->framebuffer->Width;
    screenHeight = bootInfo->framebuffer->Height;
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;
    PageFrameAllocator newAllocator;
    newAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    newAllocator.LockPages(&_KernelStart, kernelPages);
    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize+0x1000;
    newAllocator.LockPages((void*)fbBase, fbSize / 0x1000 + 1);

    uint64_t screenBufferStart = fbBase + fbSize / 0x1000 + 2;
    uint64_t screenBufferSize = (screenWidth*screenHeight)/4096;

    newAllocator.LockPages(&screenBufferStart, screenBufferSize);

    graphics->preRenderedBuffer = (size_t*)(fbBase+fbSize);

    graphics->clear(0xffff0000);
    graphics->render();
}