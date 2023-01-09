#include <stddef.h>
#include "BitOSDatatypes.h"
#include "BitOSUtilities.h"
#include "ToString.h"
#include "efiMemory.h"
#include "Graphics.h"
#include "portIO.h"
#include "keyboard.h"
#include "renderWindow.h"
#include "kernelUtil.h"
#include "GraphicsHelper.h"
#include "SerialPorts.h"

Graphics* graphics;
extern uint64_t screenWidth;
extern uint64_t screenHeight;

extern "C" void _start(BootInfo* bootInfo){
    Graphics g = Graphics(bootInfo->framebuffer, bootInfo->psf1_Font);
    graphics = &g;

    bootHelper(bootInfo);

    // int* test = (int*)0x80000000000;
    // *test = 2; 
    
    graphics->clear(0xff0fff);
    Window textEdit = {"Notepad", 50, 200, 400, 100, 0b1101}; //{full minimize highlighted}, {maximize/slight minimize hightlight}, {maximise(1) or slight minimize(0)}, {window closed highlighted}
    renderWindow(&textEdit);
    while(true){}
    return;
}

