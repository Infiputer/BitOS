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

    exePage[0] = 0x03; //  ADD mloc + mloc

    exePage[1] = 2; // 2 bytes, uint16_t

    exePage[2] = 0;  // memory location 2 pointer
    exePage[3] = 0;  // memory location 1 pointer
    exePage[4] = 0;  // memory location 1 pointer
    exePage[5] = 0;  // memory location 1 pointer
    exePage[6] = 0;  // memory location 1 pointer
    exePage[7] = 0;  // memory location 1 pointer
    exePage[8] = 0;  // memory location 1 pointer
    exePage[9] = 19; // memory location 1 pointer

    exePage[10] = 0;  // memory location 2 pointer
    exePage[11] = 0;  // memory location 2 pointer
    exePage[12] = 0;  // memory location 2 pointer
    exePage[13] = 0;  // memory location 2 pointer
    exePage[14] = 0;  // memory location 2 pointer
    exePage[15] = 0;  // memory location 2 pointer
    exePage[16] = 0;  // memory location 2 pointer
    exePage[17] = 21; // memory location 2 pointer

    exePage[18] = 0; // end program

    exePage[19] = 0xab; // 0xabab (43947)
    exePage[20] = 0xab; // 0xabab (43947)

    exePage[21] = 0x10; // 0x1020 (4128) 
    exePage[22] = 0x20; // 0x1020 (4128)

    exe.InitExe(23); // size of exe
    exe.addPage(exePage);

    for (uint8_t i = 0; i < 3; i++)
    {
        exe.RunStep();
    }

    log(to_string(((uint64_t)exePage[19]) * 256 + exePage[20])); // 43947 + 4128 = 48075

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