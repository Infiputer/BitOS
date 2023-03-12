#include <stddef.h>
#include "BitOSDatatypes.h"
#include "BitOSUtilities.h"
#include "ToString.h"
#include "graphics/Graphics.h"
#include "panels/renderPanel.h"
#include "kernelUtil.h"
#include "keyboard/KeyPressType.h"
#include "panels/panel.h"
#include "graphics/renderGUI.h"
#include "cryptography/hash.h"

Graphics *graphics;
extern uint64_t screenWidth;
extern uint64_t screenHeight;

#define maxKeysDown 8
extern volatile KeyPress keysPressed[maxKeysDown];

extern "C" void _start(BootInfo *bootInfo) // Start function
{

    bootHelper(bootInfo);
    log("BitOS Started!", LOG_GREEN);

    while (true)
    {
        asm("hlt");
    }
    return;
}