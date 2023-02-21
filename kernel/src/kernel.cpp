#include <stddef.h>
#include "BitOSDatatypes.h"
#include "BitOSUtilities.h"
#include "ToString.h"
#include "efiMemory.h"
#include "Graphics.h"
#include "portIO.h"
#include "keyboard/KeyboardTranslation.h"
#include "panels/renderPanel.h"
#include "kernelUtil.h"
#include "GraphicsHelper.h"
#include "keyboard/KeyPressType.h"
#include "mouse/mouse.h"
#include "panels/panel.h"

Graphics *graphics;
extern uint64_t screenWidth;
extern uint64_t screenHeight;

#define maxKeysDown 8
extern volatile KeyPress keysPressed[maxKeysDown];

extern "C" void _start(BootInfo *bootInfo) // Start function
{
    Graphics g = Graphics(bootInfo->framebuffer, bootInfo->psf1_Font);
    graphics = &g;
    bootHelper(bootInfo);
    graphics->clear(0xffffff);
    graphics->print(0, "Kernel Initalized", 0, 0);
    
    renderPanels();
    while(true){
        asm("hlt");
    }
    return;
}