#include "DoubleBuffering.h"
#include "GraphicsHelper.h"
#include "../memory/memory.h"
#include "../paging/PageFrameAllocator.h"
#include "Graphics.h"
#include "../ToString.h"

void Graphics::enableDoubleBuffering()
{
    log("Creating RED back buffer");

    for (uint32_t i = 0; i < DoubleBufferMainSize; i++)
    {
        doubleBufferArrayRED[i] = (uint8_t *)GlobalAllocator.RequestPage();
        if (doubleBufferArrayRED[i] == nullptr)
        {
            log("Memory ran out", LOG_RED);
            return;
        }
    }
    log("Finished creating RED back buffer");

    log("Creating GREEN back buffer");

    for (uint32_t i = 0; i < DoubleBufferMainSize; i++)
    {
        doubleBufferArrayGREEN[i] = (uint8_t *)GlobalAllocator.RequestPage();
        if (doubleBufferArrayGREEN[i] == nullptr)
        {
            log("Memory ran out", LOG_RED);
            return;
        }
    }
    log("Finished creating GREEN back buffer");

    log("Creating BLUE back buffer");

    for (uint32_t i = 0; i < DoubleBufferMainSize; i++)
    {
        doubleBufferArrayBLUE[i] = (uint8_t *)GlobalAllocator.RequestPage();
        if (doubleBufferArrayBLUE[i] == nullptr)
        {
            log("Memory ran out", LOG_RED);
            return;
        }
    }
    log("Finished creating BLUE back buffer");

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