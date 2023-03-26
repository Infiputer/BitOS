#include "DoubleBuffering.h"
#include "GraphicsHelper.h"
#include "../memory/memory.h"
#include "../paging/PageFrameAllocator.h"
#include "Graphics.h"
#include "../ToString.h"
#include "../BitOSUtilities.h"

void Graphics::enableDoubleBuffering()
{
    uint32_t DoubleBufferMainSizeActual = totalScreenSize / 4096 + 1;
    log("Creating back buffer");
    for (uint32_t i = 0; i < DoubleBufferMainSizeActual; i++)
    {
        doubleBufferArrayRED[i] = (uint8_t *)GlobalAllocator.RequestPage();
        doubleBufferArrayGREEN[i] = (uint8_t *)GlobalAllocator.RequestPage();
        doubleBufferArrayBLUE[i] = (uint8_t *)GlobalAllocator.RequestPage();
        if (
            doubleBufferArrayRED[i] == nullptr ||
            doubleBufferArrayGREEN[i] == nullptr ||
            doubleBufferArrayBLUE[i] == nullptr)
        {
            log("Memory ran out", LOG_RED);
            return;
        }

        while (!checkPage(doubleBufferArrayRED[i]))
            doubleBufferArrayRED[i] = (uint8_t *)GlobalAllocator.RequestPage();

        while (!checkPage(doubleBufferArrayGREEN[i]))
            doubleBufferArrayGREEN[i] = (uint8_t *)GlobalAllocator.RequestPage();

        while (!checkPage(doubleBufferArrayBLUE[i]))
            doubleBufferArrayBLUE[i] = (uint8_t *)GlobalAllocator.RequestPage();
    }
    log("Finished creating back buffer");

    doubleBufferingEnabled = true;
}

void Graphics::drawPixel(uint32_t color, uint32_t x, unsigned y)
{
    if (x > TargetFramebuffer->Width - 1 || y > TargetFramebuffer->Height - 1)
        return;
    if (doubleBufferingEnabled)
    {
        uint64_t index = x + (y * TargetFramebuffer->PixelsPerScanLine);
        uint64_t pointerIndex = index / 4096; // calculate the index of the pointer in largeArray
        uint64_t offset = index % 4096;       // calculate the offset within the pointed-to array
        *(doubleBufferArrayRED[pointerIndex] + offset) = (color >> 16) & 0xFF;
        *(doubleBufferArrayGREEN[pointerIndex] + offset) = (color >> 8) & 0xFF;
        *(doubleBufferArrayBLUE[pointerIndex] + offset) = color & 0xFF;
    }
    else
    {
        *(uint32_t *)((uint32_t *)pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color;
    }
}

uint32_t Graphics::GetPix(uint32_t x, uint32_t y)
{
    if (doubleBufferingEnabled)
    {
        uint64_t index = x + (y * TargetFramebuffer->PixelsPerScanLine);
        uint64_t pointerIndex = index / 4096; // calculate the index of the pointer in largeArray
        uint64_t offset = index % 4096;       // calculate the offset within the pointed-to array
        return color_rgb(
            *(doubleBufferArrayRED[pointerIndex] + offset),
            *(doubleBufferArrayGREEN[pointerIndex] + offset),
            *(doubleBufferArrayBLUE[pointerIndex] + offset));
    }
    else
    {
        return *(uint32_t *)((uint64_t)TargetFramebuffer->BaseAddress + (x * 4) + (y * TargetFramebuffer->PixelsPerScanLine * 4));
    }
}

void Graphics::render()
{
    if (doubleBufferingEnabled)
    {
        for (uint64_t i = 0; i < totalScreenSize; i++)
        {
            uint64_t pointerIndex = i / 4096; // calculate the index of the pointer in largeArray
            uint64_t offset = i % 4096;       // calculate the offset within the pointed-to array
            *(uint32_t *)((uint32_t *)pixPtr + i) = color_rgb(
                *(doubleBufferArrayRED[pointerIndex] + offset),
                *(doubleBufferArrayGREEN[pointerIndex] + offset),
                *(doubleBufferArrayBLUE[pointerIndex] + offset));
        }
    }
};