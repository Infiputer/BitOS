#include <stddef.h>
#include "efiMemory.h"
#include "FrameBuffer.h"
#include "FontDefinitions.h"
#include "BitOSDatatypes.h"
#include "BitOSUtilities.h"
#include "ToString.h"
#include "FontDefinitions.h"
#include "Graphics.h"
#include "portIO.h"
#include "keyboard.h"
#include "renderWindow.h"

#define color_rgba(r, g, b, a) ((unsigned int)((unsigned int)0x01000000*a+(unsigned int)0x00010000*r+(unsigned int)0x00000100*g+(unsigned int)0x00000001*b))
Point textCursor; 
Point WriteLineCursor;

uint64_t screenWidth = 1920;
uint64_t screenHeight = 1080;

size_t screenPreBuffer[1920*1080];

extern Graphics* graphics;
extern "C" void _start(BootInfo* bootInfo){
    Graphics g = Graphics(bootInfo->framebuffer, bootInfo->psf1_Font);
    graphics = &g;
    screenWidth = bootInfo->framebuffer->Width;
    screenHeight = bootInfo->framebuffer->Height;
    for(int i = 0; i < (screenHeight*screenWidth); i++){
        screenPreBuffer[i] = color_rgba(255, 255, 255, 255);
    }
    graphics->preRenderedBuffer = screenPreBuffer;
    graphics->render();
    while(true){
        for(double i = 0; i < screenWidth-400; i+=0.5){
            graphics->clear(color_rgba(255, 100, 255, 255));
            Window textEdit = {"Notepad", (uint64_t)i, 200, 400, 100};
            renderWindow(&textEdit);
        }
        for(double i = screenWidth-400; i > 0; i-=0.5){
            graphics->clear(color_rgba(255, 100, 255, 255));
            Window textEdit = {"Notepad", (uint64_t)i, 200, 400, 100};
            renderWindow(&textEdit);
        }
    }
    return;
} 