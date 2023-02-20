#include "Graphics.h"

Graphics::Graphics(Framebuffer *targetFramebuffer, PSF1_FONT *psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    totalScreenSize = (TargetFramebuffer->PixelsPerScanLine) * (TargetFramebuffer->Height);
    pixPtr = (unsigned int *)TargetFramebuffer->BaseAddress;
}
void Graphics::clear(unsigned int color)
{
    for (unsigned int i = 0; i < totalScreenSize; i++)
    {
        *(unsigned int *)(pixPtr + i) = color;
    }
}
void Graphics::drawPixel(unsigned int color, unsigned int x, unsigned y)
{
    *(unsigned int *)((unsigned int *)pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color;
}
void Graphics::fillRect(unsigned int color, unsigned int xOff, unsigned int yOff, unsigned int width, unsigned int height)
{
    for (unsigned drawX = xOff; drawX < xOff + width; drawX++)
    {
        for (unsigned drawY = yOff; drawY < yOff + height; drawY++)
        {
            drawPixel(color, drawX, drawY);
        }
    }
}

void Graphics::drawRect(unsigned int color, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    for (uint64_t x1 = x; x1 < x + width + 1; x1++)
    {
        drawPixel(color, x1, y);
        drawPixel(color, x1, y + height);
    }
    for (uint64_t y1 = y; y1 < y + height; y1++)
    {
        drawPixel(color, x, y1);
        drawPixel(color, x + width, y1);
    }
}

void Graphics::putChar(unsigned int color, char chr, unsigned int xOff, unsigned int yOff, float width, float height)
{
    char *fontPtr = (char *)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 20; y++)
    {
        for (unsigned long x = xOff; x < xOff + 8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                *(unsigned int *)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color;
            }
        }
        fontPtr++;
    }
}

unsigned int Graphics::print(unsigned int color, const char *str, unsigned int xOff, unsigned int yOff, float width, float height)
{

    char *chr = (char *)str;
    while (*chr != 0)
    {
        putChar(color, *chr, xOff, yOff, width, height);
        xOff += 8;
        if (xOff > TargetFramebuffer->Width)
        {
            xOff = 0;
            yOff += 20;
        }
        chr++;
    }
    return xOff;
}