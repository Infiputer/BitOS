#include "Graphics.h"
Graphics::Graphics(Framebuffer *targetFramebuffer, PSF1_FONT *psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    totalScreenSize = (TargetFramebuffer->PixelsPerScanLine) * (TargetFramebuffer->Height);
    pixPtr = (unsigned int *)TargetFramebuffer->BaseAddress;
}
uint32_t Graphics::GetPix(uint32_t x, uint32_t y)
{
    return *(uint32_t *)((uint64_t)TargetFramebuffer->BaseAddress + (x * 4) + (y * TargetFramebuffer->PixelsPerScanLine * 4));
}
void Graphics::ClearMouseCursor(uint8_t *mouseCursor, Point position)
{
    if (!MouseDrawn)
        return;
    int xMax = 16;
    int yMax = 16;
    int differenceX = TargetFramebuffer->Width - position.X;
    int differenceY = TargetFramebuffer->Height - position.Y;
    if (differenceX < 16)
        xMax = differenceX;
    if (differenceY < 16)
        yMax = differenceY;
    for (int y = 0; y < yMax; y++)
    {
        for (int x = 0; x < xMax; x++)
        {
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8))))
            {
                if (GetPix(position.X + x, position.Y + y) == MouseCursorBufferAfter[x + y * 16])
                {
                    drawPixel(MouseCursorBuffer[x + y * 16], position.X + x, position.Y + y);
                }
            }
        }
    }
}
void Graphics::DrawOverlayMouseCursor(uint8_t *mouseCursor, Point position)
{
    int xMax = 16;
    int yMax = 16;
    int differenceX = TargetFramebuffer->Width - position.X;
    int differenceY = TargetFramebuffer->Height - position.Y;
    if (differenceX < 16)
        xMax = differenceX;
    if (differenceY < 16)
        yMax = differenceY;
    for (int y = 0; y < yMax; y++)
    {
        for (int x = 0; x < xMax; x++)
        {
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8))))
            {
                MouseCursorBuffer[x + y * 16] = GetPix(position.X + x, position.Y + y);
                uint32_t colorCode = MouseCursorBuffer[x + y * 16];
                uint8_t r = (colorCode >> 16) & 0xFF;
                uint8_t g = (colorCode >> 8) & 0xFF;
                uint8_t b = colorCode & 0xFF;
                drawPixel(((r+g+b)/3 > 20)?0x00001f:0xefffef, position.X + x, position.Y + y);
                MouseCursorBufferAfter[x + y * 16] = GetPix(position.X + x, position.Y + y);
            }
        }
    }
    MouseDrawn = true;
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