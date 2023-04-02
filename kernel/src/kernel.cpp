#include <stddef.h>
#include "BitOSDatatypes.h"
#include "BitOSUtilities.h"
#include "ToString.h"
#include "graphics/Graphics.h"
#include "panels/renderPanel.h"
#include "kernelUtil.h"
#include "graphics/renderGUI.h"
#include "executables/ExecutableRegisters.h"

ExeRegisters exeR;
extern "C" void _start(BootInfo *bootInfo) // Start function
{

    bootHelper(bootInfo);
    log("BitOS Started!", LOG_GREEN);
    log("Testing Registers");

    exeR.clear();
    exeR.setRegister(14, 0xabcdef123);
    log("Got:", 0, 0, 0);
    log(to_hstring(exeR.getRegister(14)), 0, 0, 0);
    log("; Expected 0xABCDEF123");

    exeR.clear();
    exeR.setRegister(7, 0xff);
    log("Got:", 0, 0, 0);
    log(to_hstring(exeR.getRegister(14)), 0, 0, 0);
    log("; Expected 0xFF");

    exeR.clear();
    exeR.setRegister(12, 0x12345);
    exeR.setRegister(13, 0xabcdef);
    log("Got:", 0, 0, 0);
    log(to_hstring(exeR.getRegister(14)), 0, 0, 0);
    log("; Expected 0x0001234500abcdef");

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