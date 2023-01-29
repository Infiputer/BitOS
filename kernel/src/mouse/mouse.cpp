#include "mouse.h"

void MouseWait()
{
    uint64_t timeout = 100000;
    while (timeout--)
    {
        if ((inb(0x64) & 0b10) == 0)
        {
            return;
        }
    }
}

void MouseWaitInput()
{
    uint64_t timeout = 100000;
    while (timeout--)
    {
        if (inb(0x64) & 0b1)
        {
            return;
        }
    }
}

void MouseWrite(uint8_t value)
{
    MouseWait();
    outb(0x64, 0xD4);
    MouseWait();
    outb(0x60, value);
}

uint8_t MouseRead()
{
    MouseWaitInput();
    return inb(0x60);
}

uint8_t MouseCycle = 0;
uint8_t MousePacket[4];

Point MousePosition;
void HandlePS2Mouse(uint8_t data)
{
    switch (MouseCycle)
    {
    case 0:
        if (data & 0b00001000 == 0)
            break;
        MousePacket[0] = data;
        MouseCycle++;
        break;
    case 1:
        MousePacket[1] = data;
        MouseCycle++;
        break;
    case 2:
        MousePacket[2] = data;
        MouseCycle = 0;
        ProcessMousePacket();
        break;
    }
}

bool xNegative = false;
bool yNegative = false;
bool xOverflow = false;
bool yOverflow = false;
void ProcessMousePacket()
{
    xNegative = (MousePacket[0] & PS2XSign) != 0;
    yNegative = (MousePacket[0] & PS2YSign) != 0;
    xOverflow = (MousePacket[0] & PS2XOverflow) != 0;
    yOverflow = (MousePacket[0] & PS2YOverflow) != 0;

    if (!xNegative)
    {
        MousePosition.X += MousePacket[1];
        if (xOverflow)
            MousePosition.X += 255;
    }
    else
    {
        MousePacket[1] = 256 - MousePacket[1];
        MousePosition.X -= MousePacket[1];
        if (xOverflow)
            MousePosition.X -= 255;
    }
    if (!yNegative)
    {
        MousePosition.Y -= MousePacket[2];
        if (yOverflow)
            MousePosition.Y -= 255;
    }
    else
    {
        MousePacket[2] = 256 - MousePacket[2];
        MousePosition.Y += MousePacket[2];
        if (yOverflow)
            MousePosition.Y += 255;
    }
    if (MousePosition.X < 0)
        MousePosition.X = 0;
    if (MousePosition.X > graphics->TargetFramebuffer->Width - 8)
        MousePosition.X = graphics->TargetFramebuffer->Width - 8;

    if (MousePosition.Y < 0)
        MousePosition.Y = 0;
    if (MousePosition.Y > graphics->TargetFramebuffer->Height - 16)
        MousePosition.Y = graphics->TargetFramebuffer->Height - 16;

    graphics->putChar(0, '^', MousePosition.X, MousePosition.Y); //mouse pointer
}

void InitPS2Mouse()
{

    outb(0x64, 0xA8); // enabling the auxiliary device - mouse

    MouseWait();
    outb(0x64, 0x20); // tells the keyboard controller that we want to send a command to the mouse
    MouseWaitInput();
    uint8_t status = inb(0x60);
    status |= 0b10;
    MouseWait();
    outb(0x64, 0x60);
    MouseWait();
    outb(0x60, status); // setting the correct bit is the "compaq" status byte

    MouseWrite(0xF6);
    MouseRead();

    MouseWrite(0xF4);
    MouseRead();
}