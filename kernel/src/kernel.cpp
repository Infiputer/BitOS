#include <stddef.h>
#include <cstring>
#include <cstdlib>
#include "efiMemory.h"
#include "FrameBuffer.h"
#include "FontDefinitions.h"
#include "BitOSDatatypes.h"
#include "BitOSUtilities.h"
#include "ToString.h"
#include "FontDefinitions.h"
#include "Graphics.h"
#include "textEditor.h"
#include "portIO.h"
#include "keyboard.h"

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;
#define color_rgba(r, g, b, a) ((unsigned int)((unsigned int)0x01000000*a+(unsigned int)0x00010000*r+(unsigned int)0x00000100*g+(unsigned int)0x00000001*b))
Point textCursor; 
Point WriteLineCursor;
#define WriteLine(s) WriteLineCursor.X = graphics.print(0x0, s, WriteLineCursor.X, WriteLineCursor.Y);
#define WriteNewLine() WriteLineCursor.Y+=21; WriteLineCursor.X=0
#define screenWidth 1920
#define screenHeight 1080
void renderTextEditor(Graphics g, const char* text){
    // g.fillRect(color_rgba(41, 45, 62, 255), 0, 0, 1920, 1080);
    g.fillRect(color_rgba(255, 0, 0, 255), 0, 0, 1920, 1080);
    // g.fillRect(color_rgba(0, 128, 255, 255), 0, 0, screenWidth, 40);
    g.print(color_rgba(0, 0, 0, 255), "New File", screenWidth/2-(3.5*16)+2, 6, 2, 2);
    g.print(color_rgba(255, 255, 255, 255), "New File", screenWidth/2-(3.5*16), 3, 2, 2);
    
    unsigned int i = 0;
    unsigned int xPosition = 0;
    unsigned int yPosition = 50;

    while(text[i] != 0){
        if(text[i] == '\n'){
            yPosition += 22;
            xPosition = 0;
        }
        else{
            g.putChar(color_rgba(255, 255, 255, 255), text[i], xPosition, yPosition, 1.5, 1.5);
            xPosition += 13;
        }
        i++;
    }
    g.render();
}
size_t screenPreBuffer[screenHeight*screenWidth];
extern "C" void _start(BootInfo* bootInfo){
    Graphics graphics = Graphics(bootInfo->framebuffer, bootInfo->psf1_Font);
    for(int i = 0; i < (screenHeight*screenWidth); i++){
        screenPreBuffer[i] = 0xffffffff;
    }
    graphics.preRenderedBuffer = screenPreBuffer;
    graphics.render();

    // graphics.fillRect(color_rgba(255, 0, 0, 255), 0, 0,  1920/6, 1080);
    // graphics.fillRect(color_rgba(255, 128, 0, 255), 1920/6, 0,  1920/6, 1080);
    // graphics.fillRect(color_rgba(255, 255, 0, 255), 1920/6*2, 0,  1920/6, 1080);
    // graphics.fillRect(color_rgba(0, 255, 50, 255), 1920/6*3, 0,  1920/6, 1080);
    // graphics.fillRect(color_rgba(0, 100, 255, 255), 1920/6*4, 0,  1920/6, 1080);
    // graphics.fillRect(color_rgba(255, 0, 255, 255), 1920/6*5, 0,  1920/6, 1080);
    // graphics.render();
    return;
    init_pics(0x20, 0x28);//init keyboard
    renderTextEditor(graphics, "\nabcdef\nabcdef\nabcdef\nabcdef\ngdagd\ngdf\nhfghfsh");
    char readChar = '\0';
    char editor[(1920/16) * (1080/16)];
    for(int i = 0; i < (1920/16)*(1080/16); i++){
        editor[i] = '\0';
    }
    Point CursorPosition;
    while(true){
        if(inb(0x60) != readChar){
            readChar = inb(0x60);
            if(readChar > 0){
                NormalKeyboardKey normalKey = scancode2normal(readChar);
                if(normalKey.keyType == 2){
                    editor[CursorPosition.X+(CursorPosition.Y*(1080/16))] = normalKey.key;
                    CursorPosition.X++; 
                }
                if(normalKey.keyType == 0){
                    CursorPosition.X--; 
                }
                WriteLine(to_string((uint64_t)readChar));
                renderTextEditor(graphics, editor);
            }
        }
    }
    return;
} 