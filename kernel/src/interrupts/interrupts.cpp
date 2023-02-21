#include <stddef.h>
#include "interrupts.h"
#include "../panic.h"
#include "../portIO.h"
#include "../keyboard/KeyboardTranslation.h"
#include "../keyboard/KeyPressType.h"
#include "../Graphics.h"
#include "../mouse/mouse.h"

#define maxKeysDown 8
volatile KeyPress keysPressed[maxKeysDown] = {{0, 127, 0}, {0, 127, 0}, {0, 127, 0}, {0, 127, 0}, {0, 127, 0}, {0, 127, 0}, {0, 127, 0}, {0, 127, 0}};

/**
 * Page Fault interrupt handler.
 *
 * @param frame Pointer to the interrupt frame
 *
 * This function is called when a page fault is detected. It prints an error
 * message and enters an infinite loop, as the system panic is triggered.
 */
__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame *frame)
{
    SysPanic("Page Fault Detected");
    while (true)
        asm("hlt");
}

/**
 * Double Fault interrupt handler.
 *
 * @param frame Pointer to the interrupt frame
 *
 * This function is called when a Double fault is detected. It prints an error
 * message and enters an infinite loop, as the system panic is triggered.
 */
__attribute__((interrupt)) void DoubleFault_Handler(struct interrupt_frame *frame)
{
    SysPanic("Double Fault Detected");
    while (true)
        asm("hlt");
}

/**
 * General Protectio Fault interrupt handler.
 *
 * @param frame Pointer to the interrupt frame
 *
 * This function is called when a General Protection fault is detected. It prints an error
 * message and enters an infinite loop, as the system panic is triggered.
 */
__attribute__((interrupt)) void GPFault_Handler(struct interrupt_frame *frame)
{
    SysPanic("General Protection Fault Detected");

    while (true)
        asm("hlt");
}

/**
 * Interrupt handler for PS/2 Mouse event
 *
 * @param frame Pointer to the interrupt frame
 */
__attribute__((interrupt)) void MouseInt_Handler(interrupt_frame *frame)
{

    uint8_t mouseData = inb(0x60);
    HandlePS2Mouse(mouseData);
    PIC_EndSlave();
}

#define absScanCode(c) ((c < 0) ? 128 - (0 - c) : c)

// Scancode of the Keyboard Interrupt handler
char scancode = 0;
// Normal key for Keyboard Interrupt handler
NormalKeyboardKey key;

/**
 * Interrupt handler for PS/2 Keyboard event
 *
 * @param frame Pointer to the interrupt frame
 */
__attribute__((interrupt)) void KeyboardInt_Handler(struct interrupt_frame *frame)
{
    scancode = inb(0x60);
    key = scancode2normal(absScanCode(scancode));
    if (scancode > 0)
    {
        for (uint8_t i = 0; i < maxKeysDown; i++)
        {
            if (keysPressed[i].key == key.key && keysPressed[i].keyType == key.keyType) // key press is already registered
            {
                break;
            }
            if (keysPressed[i].key == 0 && keysPressed[i].keyType == 127)
            {
                keysPressed[i].key = key.key;
                keysPressed[i].keyType = key.keyType;
                keysPressed[i].timeHeld = 0;
                break;
            }
        }
    }
    else
    {
        for (uint8_t i = 0; i < maxKeysDown; i++)
        {
            if (keysPressed[i].key == key.key && keysPressed[i].keyType == key.keyType)
            {
                keysPressed[i].key = 0;
                keysPressed[i].keyType = 127;
                keysPressed[i].timeHeld = 0;
            }
        }
    }

    PIC_EndMaster();
}

/**
 * Sends End-of-Interrupt signal to Master PIC
 */
void PIC_EndMaster()
{
    outb(PIC1_COMMAND, PIC_EOI);
}

/**
 * Sends End-of-Interrupt signal to both Master and Slave PIC
 */
void PIC_EndSlave()
{
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}

void RemapPIC()
{
    uint8_t a1, a2;

    a1 = inb(PIC1_DATA);
    io_wait();
    a2 = inb(PIC2_DATA);
    io_wait();

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, 0x20);
    io_wait();
    outb(PIC2_DATA, 0x28);
    io_wait();

    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);
}