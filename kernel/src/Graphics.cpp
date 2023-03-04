#include "Graphics.h"
Graphics::Graphics(Framebuffer *targetFramebuffer, PSF1_FONT *psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    totalScreenSize = (TargetFramebuffer->PixelsPerScanLine) * (TargetFramebuffer->Height);
    pixPtr = (uint32_t *)TargetFramebuffer->BaseAddress;
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
                drawPixel(((r + g + b) / 3 > 20) ? 0x00001f : 0xefffef, position.X + x, position.Y + y);
                MouseCursorBufferAfter[x + y * 16] = GetPix(position.X + x, position.Y + y);
            }
        }
    }
    MouseDrawn = true;
}
void Graphics::clear(uint32_t color)
{
    for (uint32_t i = 0; i < totalScreenSize; i++)
    {
        *(uint32_t *)(pixPtr + i) = color;
    }
}
void Graphics::drawPixel(uint32_t color, uint32_t x, unsigned y)
{
    if (x > TargetFramebuffer->Width - 1 || y > TargetFramebuffer->Height - 1)
        return;
    *(uint32_t *)((uint32_t *)pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color;
}
void Graphics::fillRect(uint32_t color, int32_t xOff, int32_t yOff, int32_t width, int32_t height)
{
    for (int32_t drawX = xOff; drawX < xOff + width; drawX++)
    {
        for (int32_t drawY = yOff; drawY < yOff + height; drawY++)
        {
            if (drawX >= 0 && drawY >= 0)
                drawPixel(color, drawX, drawY);
        }
    }
}
void Graphics::drawRect(uint32_t color, int32_t x, int32_t y, int32_t width, int32_t height)
{
    for (int32_t x1 = x; x1 < x + width + 1; x1++)
    {
        drawPixel(color, x1, y);
        drawPixel(color, x1, y + height);
    }
    for (int32_t y1 = y; y1 < y + height; y1++)
    {
        drawPixel(color, x, y1);
        drawPixel(color, x + width, y1);
    }
}
void Graphics::putChar(uint32_t color, char chr, int32_t xOff, int32_t yOff, float width, float height)
{
    char *fontPtr = (char *)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
    for (int64_t y = yOff; y < yOff + 20; y++)
    {
        for (int64_t x = xOff; x < xOff + 8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                *(uint32_t *)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color;
            }
        }
        fontPtr++;
    }
}
uint32_t Graphics::print(uint32_t color, const char *str, int32_t xOff, int32_t yOff, float width, float height)
{
    char *chr = (char *)str;
    while (*chr != 0)
    {
        if (xOff >= 0)
            putChar(color, *chr, xOff, yOff, width, height);
        xOff += 8;
        if (xOff > TargetFramebuffer->Width)
            return xOff;
        chr++;
    }
    return xOff;
}

void Graphics::render(){

};