#include <stddef.h>
#include "BitOSDatatypes.h"
#include "BitOSUtilities.h"
#include "ToString.h"
#include "Graphics.h"
#include "panels/renderPanel.h"
#include "kernelUtil.h"
#include "keyboard/KeyPressType.h"
#include "panels/panel.h"
#include "SysGraphics/renderGUI.h"

Graphics *graphics;
extern uint64_t screenWidth;
extern uint64_t screenHeight;

#define maxKeysDown 8
extern volatile KeyPress keysPressed[maxKeysDown];

extern "C" void _start(BootInfo *bootInfo) // Start function
{

    bootHelper(bootInfo);
    graphics->clear(0x00ffff);
    graphics->print(0, "Kernel Initalized", 0, 0);

    while(true){
        asm("hlt");
    }
    return;
}