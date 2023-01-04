#pragma once
#include "FrameBuffer.h"
#include "FontDefinitions.h"
#include "math.h"

class Graphics{
    public:
        Framebuffer* TargetFramebuffer;
        PSF1_FONT* PSF1_Font;
        size_t *preRenderedBuffer;
        unsigned int* pixPtr;
        uint64_t totalScreenSize;
        
        Graphics(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font)
        {
            TargetFramebuffer = targetFramebuffer;
            PSF1_Font = psf1_Font;
            totalScreenSize = (TargetFramebuffer->PixelsPerScanLine)*(TargetFramebuffer->Height);
            //unsigned int pointerPreRenderedBuffer[TargetFramebuffer->PixelsPerScanLine*TargetFramebuffer->Height];
            pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
            //preRenderedBuffer = pointerPreRenderedBuffer;
        }

        void clear(unsigned int color){
            for(unsigned int i = 0; i < (TargetFramebuffer->PixelsPerScanLine)*(TargetFramebuffer->Height); i++){
                preRenderedBuffer[i] = color;
            }
        }
        void drawPixel(unsigned int color, unsigned int x, unsigned y){
            preRenderedBuffer[x + y * TargetFramebuffer->PixelsPerScanLine] = color;
            //unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
            //*(unsigned int*)((unsigned int*)TargetFramebuffer->BaseAddress + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color;
        }
        void render(){
            for(unsigned int i = 0; i < totalScreenSize; i++){
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

        void drawLine(unsigned int color, double x1, double y1, double x2, double y2, unsigned int thickness = 1){
            unsigned int dist = distance(x1, y1, x2, y2);
            double xDist = abs(x2-x1);
            double yDist = abs(y2-y1);
            for(int i = 0; i < dist; i++){
                fillRect(
                    color,
                    x1,
                    y1,
                    thickness, thickness
                );
                x1 = constantlerp(x1, x2, xDist/dist);
                y1 = constantlerp(y1, y2, yDist/dist);
            }
        }
        void drawRect(unsigned int color, unsigned int x, unsigned int y, unsigned int width, unsigned int height){
            drawLine(color, x, y, x+width, y);
            drawLine(color, x, y+height, x+width+1, y+height);
            drawLine(color, x, y, x, y+height);
            drawLine(color, x+width, y, x+width, y+height);
        }
        void drawCircle(unsigned int color, unsigned int xOff, unsigned int yOff, unsigned int radius, unsigned int sides = 50){
            double incrementValue = 6.28/sides;
            for(double rad = 0; rad < 6.28; rad+=incrementValue){
                drawPixel(color, xOff+cos(rad)*radius, yOff+sin(rad)*radius);
            }
        }
        void fillCircle(unsigned int color, unsigned int xOff, unsigned int yOff, unsigned int radius, unsigned int sides = 100, double rotation = 0){
            double incrementValue = TWO_PI/sides;
            for(double rad = rotation; rad < TWO_PI+rotation; rad+=incrementValue){
                double cosResult1 = cos(rad);
                double sinResult1 = sin(rad);
                double cosResult2 = cos(rad+incrementValue);
                double sinResult2 = sin(rad+incrementValue);
                drawLine(color, xOff, yOff, xOff+cosResult1*radius, yOff+sinResult1*radius);
                for(unsigned radius2 = 0; radius2 < radius; radius2++){
                    drawLine(
                        color,
                        xOff+cosResult1*radius2,
                        yOff+sinResult1*radius2,
                        xOff+cosResult2*radius2,
                        yOff+sinResult2*radius2
                    );
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


