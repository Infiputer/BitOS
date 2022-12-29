#pragma once
#include "FrameBuffer.h"
#include "FontDefinitions.h"

class Graphics{
    public:
        Framebuffer* TargetFramebuffer;
        PSF1_FONT* PSF1_Font;

        size_t *preRenderedBuffer;

        Graphics(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font)
        {
            TargetFramebuffer = targetFramebuffer;
            PSF1_Font = psf1_Font;
            //unsigned int pointerPreRenderedBuffer[TargetFramebuffer->PixelsPerScanLine*TargetFramebuffer->Height];
            //preRenderedBuffer = pointerPreRenderedBuffer;
        }

        void drawPixel(unsigned int color, unsigned int x, unsigned y){
            preRenderedBuffer[x + y * TargetFramebuffer->PixelsPerScanLine] = color;
            //unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
            //*(unsigned int*)((unsigned int*)TargetFramebuffer->BaseAddress + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color;
        }
        void render(){
            for(unsigned int i = 0; i < (TargetFramebuffer->PixelsPerScanLine)*(TargetFramebuffer->Height); i++){
                unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
                *(unsigned int*)(pixPtr + i) = preRenderedBuffer[i];
            }
        }
        void fillRect(unsigned int color, unsigned int xOff, unsigned int yOff, unsigned int width, unsigned int height){
            for(unsigned drawX = xOff; drawX < xOff+width; drawX++){
                for(unsigned drawY = yOff; drawY < yOff+height; drawY++){
                    drawPixel(color, drawX, drawY);
                }   
            }
        }


        void putChar(unsigned int color, char chr, unsigned int xOff, unsigned int yOff, float width = 1, float height = 1)
        {
            unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
            char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
            for (unsigned long y = 0; y < 20; y++){
                for (unsigned long x = 0; x < 8; x++){
                    if ((*fontPtr & (0b10000000 >> x)) > 0){
                        if(width == 0 && height == 0){
                            drawPixel(color, x * width + xOff, y * height + yOff);
                        }
                        else{
                            fillRect(color, x * width + xOff, y * height + yOff, width+1, height+1);
                        }
                    }
                }
                fontPtr++;
            }
        }


        unsigned int print(unsigned int color, const char* str, unsigned int xOff, unsigned int yOff, float width=1, float height=1)
        {
            
            char* chr = (char*)str;
            while(*chr != 0){
                putChar(color, *chr, xOff, yOff, width, height);
                xOff+=width*8;
                if(xOff + width * 8 > TargetFramebuffer->Width)
                {
                    xOff = 0;
                    yOff += height*16;
                }
                chr++;
            }
            return xOff;
        }    
};
