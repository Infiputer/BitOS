#include <stddef.h>
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
#include "Bitmap.h"
#include "PageFrameAllocator.h"
#include "kernelUtil.h"

#define color_rgba(r, g, b, a) ((unsigned int)((unsigned int)0x01000000*a+(unsigned int)0x00010000*r+(unsigned int)0x00000100*g+(unsigned int)0x00000001*b))

Graphics* graphics;

extern "C" void _start(BootInfo* bootInfo){
    Graphics g = Graphics(bootInfo->framebuffer, bootInfo->psf1_Font);
    graphics = &g;

    bootHelper(bootInfo);

    Window textEdit = {"Notepad", 50, 200, 400, 200};

    graphics->clear(color_rgba(0, 100, 255, 255));
       
    renderWindow(&textEdit);
    
    graphics->render();


    return;
} 