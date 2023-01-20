#pragma once
#include "Graphics.cpp"
#include "FontDefinitions.h"
class Graphics{
    public:
        void Print(Framebuffer* framebuffer, PSF1_FONT* psf1_font, unsigned int color, char* str, unsigned int xOff, unsigned int yOff, unsigned int width, unsigned int height);
        void putChar(Framebuffer* framebuffer, PSF1_FONT* psf1_font, unsigned int color, char chr, unsigned int xOff, unsigned int yOff, unsigned int width, unsigned int height);
        void fillRect(Framebuffer* framebuffer, unsigned int color, unsigned int xOff, unsigned int yOff, unsigned int width, unsigned int height);
        void drawPixel(Framebuffer* framebuffer, unsigned int color, unsigned int x, unsigned y);
};