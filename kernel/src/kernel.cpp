#include <stdint.h>
#include "BitOSDatatypes.h"
#include "BitOSUtilities.h"
#include "ToString.h"
#include "graphics/Graphics.h"
#include "panels/renderPanel.h"
#include "kernelUtil.h"
#include "graphics/renderGUI.h"
#include "executables/ExecutableClass.h"

Executable exe;
extern "C" void _start(BootInfo *bootInfo) // Start function
{

    bootHelper(bootInfo);
    log("BitOS Started!", LOG_GREEN);

    uint8_t *exePage = (uint8_t *)GlobalAllocator.RequestPage();
    uint8_t exeContent[] = {
        7, 1, 0, 0, 0, 0, 0, 0, 0, 39, 0, 0, 0, 0, 0, 0, 0, 41, 18, 0, 0, 0, 0, 0, 0, 0, 43, 7, 9, 7, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 200, 0, 100, 234
    };

    memcpy(exePage, exeContent, sizeof(exeContent));
    
    exe.InitExe(44); // size of exe
    exe.addPage(exePage);

    for (uint8_t i = 0; i < 3; i++)
    {
        exe.RunStep();
    }

    log("200 - 100 = ", 0, 0, 0);
    log(to_string(((uint64_t)exePage[39]) * 256 + exePage[40])); // 43947 + 4128 = 48075
    log("234 - 10 = ", 0, 0, 0);
    log(to_string(exe.exeRegs.getRegister(14)));

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