#include <stdint.h>
#include "BitOSDatatypes.h"
#include "BitOSUtilities.h"
#include "ToString.h"
#include "graphics/Graphics.h"
#include "panels/renderPanel.h"
#include "kernelUtil.h"
#include "graphics/renderGUI.h"
#include "executables/ExecutableClass.h"
#include "executables/exampleExe.h"

Executable exe;
extern "C" void _start(BootInfo *bootInfo) // Start function
{

    bootHelper(bootInfo);
    log("BitOS Started!", LOG_GREEN);

    uint8_t *exePage = (uint8_t *)GlobalAllocator.RequestPage();


    memcpy(exePage, exeContent, sizeof(exeContent));
    
    exe.InitExe(EXE_SIZE); // size of exe
    exe.addPage(exePage);

    for (uint8_t i = 0; i < 200; i++)
    {
        exe.RunStep();
    }

    while (true)
    {
        // asm("cli");
        // graphics->clear(0x004eff);
        // renderPanels();
        // asm("sti");
        asm("hlt");
    }
    return;
}