#include <stddef.h>
#include "BitOSDatatypes.h"
#include "BitOSUtilities.h"
#include "ToString.h"
#include "efiMemory.h"
#include "Graphics.h"
#include "portIO.h"
#include "keyboard/KeyboardTranslation.h"
#include "renderWindow.h"
#include "kernelUtil.h"
#include "GraphicsHelper.h"
#include "keyboard/KeyPressType.h"

Graphics *graphics;
extern uint64_t screenWidth;
extern uint64_t screenHeight;

#define maxKeysDown 8
extern volatile KeyPress keysPressed[maxKeysDown];

extern "C" void _start(BootInfo *bootInfo)
{
    Graphics g = Graphics(bootInfo->framebuffer, bootInfo->psf1_Font);
    graphics = &g;

    bootHelper(bootInfo);

    // int* test = (int*)0x80000000000;
    // *test = 2;

    graphics->clear(0xff0fff);
    Window textEdit = {"Notepad", 300, 100, 300, 100, 0b1101}; //{full minimize highlighted}, {maximize/slight minimize hightlight}, {maximise(1) or slight minimize(0)}, {window closed highlighted}
    renderWindow(&textEdit);
    while (true)
    {
        asm("cli");
        for (uint8_t i = 0; i < maxKeysDown; i++)
        {
            graphics->fillRect(0xff0fff, 0, i * 60, 300, 60);
            graphics->putChar(0, keysPressed[i].key, 0, i * 60);
            switch (keysPressed[i].keyType)
            {
                case 0:
                    graphics->print(0, "Control Key", 0, i * 60 + 20);
                    break;
                case 1:
                    graphics->print(0, "Function Key", 0, i * 60 + 20);
                    break;
                case 2:
                    graphics->print(0, "Ascii Key", 0, i * 60 + 20);
                    break;
                case 3:
                    graphics->print(0, "Arrow Key", 0, i * 60 + 20);
                    break;
                case 127:
                    graphics->print(0, "Not Pressed", 0, i * 60 + 20);
                    break;
                default:
                    break;
            }
            graphics->putChar(0, keysPressed[i].timeHeld, 0, i * 60 + 40);
        }

        asm("sti");
    }
    return;
}