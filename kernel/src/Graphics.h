#pragma once
#include "FrameBuffer.h"
#include "FontDefinitions.h"
#include "GraphicsHelper.h"
#include <stdint.h>

#define TWO_PI 6.283185307179586

#define FABS(x) \
  ({ \
    x < 0 ? -x : x; \
  })

#define ABS(x) \
  ({ \
    x < 0 ? -x : x; \
  })

#define SQRT(x) \
  ({ \
    double guess = 1.0; \
    for (int i = 0; i < 10; i++) { \
      guess = (guess + x / guess) / 2.0; \
    } \
    guess; \
  })

#define DISTANCE(x1, y1, x2, y2) \
  SQRT((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))

#define SIN(x) \
  ({ \
    double result = x; \
    double term = x; \
    int i = 1; \
    while (FABS(term) > 1e-6) { \
      term = -term * x * x / (2 * i + 1) / (2 * i + 2); \
      result += term; \
      i++; \
    } \
    result; \
  })

#define COS(x) \
  ({ \
    double result = 1.0; \
    double term = 1.0; \
    int i = 1; \
    while (FABS(term) > 1e-6) { \
      term = -term * x * x / (2 * i) / (2 * i + 1); \
      result += term; \
      i++; \
    } \
    result; \
  })

#define CONSTANTLERP(a, b, t) \
    ({ \
    a + (b - a) * t; \
    })

#define FMOD(a, b) \
  ({ \
    double result = a - b * floor(a / b); \
    result >= 0 ? result : result + b; \
  })

#define FLOOR(x, p) \
  ({ \
    double result = x * p; \
    result = result - (result > x * p); \
    result / p; \
  })

class Graphics{
    public:
        Framebuffer* TargetFramebuffer;
        PSF1_FONT* PSF1_Font;
        unsigned int* pixPtr;
        uint64_t totalScreenSize;
        
        Graphics(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font)
        {
            TargetFramebuffer = targetFramebuffer;
            PSF1_Font = psf1_Font;
            totalScreenSize = (TargetFramebuffer->PixelsPerScanLine)*(TargetFramebuffer->Height);
            pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
        }
        void clear(unsigned int color){
            for(unsigned int i = 0; i < totalScreenSize; i++){
                *(unsigned int*)(pixPtr + i) = color;
            }
        }
        void drawPixel(unsigned int color, unsigned int x, unsigned y){
            *(unsigned int*)((unsigned int*)pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color;
        }
        void fillRect(unsigned int color, unsigned int xOff, unsigned int yOff, unsigned int width, unsigned int height){
            for(unsigned drawX = xOff; drawX < xOff+width; drawX++){
                for(unsigned drawY = yOff; drawY < yOff+height; drawY++){
                    drawPixel(color, drawX, drawY);
                }   
            }
        }

        void drawLine(unsigned int color, double x1, double y1, double x2, double y2, unsigned int thickness = 1){
            unsigned int dist = DISTANCE(x1, y1, x2, y2);
            double xDist = ABS(x2-x1);
            double yDist = ABS(y2-y1);
            for(int i = 0; i < dist; i++){
                drawPixel(
                    color,
                    x1,
                    y1
                );
                x1 = CONSTANTLERP(x1, x2, xDist/dist);
                y1 = CONSTANTLERP(y1, y2, yDist/dist);
            }
        }
        void drawRect(unsigned int color, unsigned int x, unsigned int y, unsigned int width, unsigned int height){
            // drawLine(color, x, y, x+width, y);
            // drawLine(color, x, y+height, x+width+1, y+height);
            // drawLine(color, x, y, x, y+height);
            // drawLine(color, x+width, y, x+width, y+height);
            for(uint64_t x1 = x; x1 < x+width+1; x1++){
                drawPixel(color, x1, y);
                drawPixel(color, x1, y+height);
            }
            for(uint64_t y1 = y; y1 < y+height; y1++){
                drawPixel(color, x, y1);
                drawPixel(color, x + width, y1);
            }
        }

        void putChar(unsigned int color, char chr, unsigned int xOff, unsigned int yOff, float width = 1, float height = 1)
        {
            char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
            for (unsigned long y = yOff; y < yOff + 16; y++){
                for (unsigned long x = xOff; x < xOff+8; x++){
                    if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                            *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color;
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
                xOff+=8;
                if(xOff > TargetFramebuffer->Width)
                {
                    xOff = 0;
                    yOff += 20;
                }
                chr++;
            }
            return xOff;
        }    
};


