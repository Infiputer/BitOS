#pragma once
#include <stdint.h>
#include <cstring>
#include "GraphicsHelper.h"

extern Graphics* graphics;


struct RGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct Window{
    char title[50];
    uint64_t x;
    uint64_t y;
    uint64_t width;
    uint64_t height;
    uint8_t properties; //{full minimize highlighted}, {maximize/slight minimize hightlight}, {maximise(1) or slight minimize(0)}, {window closed highlighted}
    RGB* framebuffer;
};

#define titleBarHeight 30
#define closeDistanceFromRight 17

void renderWindow(Window* window){
    graphics->fillRect(color_rgb(59, 195, 255), window->x, window->y, window->width, titleBarHeight);
    graphics->drawRect(color_rgb(0, 0, 0), window->x, window->y, window->width, titleBarHeight);

    graphics->print(color_rgb(0, 0, 0), window->title, window->x+window->width/2-(strlen(window->title)*4) - 1, window->y+(titleBarHeight/2-10)); //prints text in black for shadow effect to the left of normal
    graphics->print(color_rgb(0, 0, 0), window->title, window->x+window->width/2-(strlen(window->title)*4) + 1, window->y+(titleBarHeight/2-10)); //prints text in black for shadow effect to the left of normal
    graphics->print(color_rgb(0, 0, 0), window->title, window->x+window->width/2-(strlen(window->title)*4)+1, window->y+(titleBarHeight/2-10)+1); //prints text in black for shadow effect to the right
    graphics->print(color_rgb(0, 0, 0), window->title, window->x+window->width/2-(strlen(window->title)*4), window->y+(titleBarHeight/2-10)-1); //prints text in black for shadow effect above the normal text
    graphics->print(color_rgb(0, 0, 0), window->title, window->x+window->width/2-(strlen(window->title)*4), window->y+(titleBarHeight/2-10)+1); //prints text in black for shadow effect below

    graphics->print(color_rgb(255, 255, 255), window->title, window->x+window->width/2-(strlen(window->title)*4), window->y+(titleBarHeight/2-10)); //prints text in white

    if((window->properties >> 0) & 1){
        graphics->fillRect(color_rgb(255, 0, 0), window->x+window->width-closeDistanceFromRight - 8, window->y+(titleBarHeight/2) - 8, 16, 16); //draw red rectangle for "X"(close)
        graphics->putChar(color_rgb(255, 255, 255), 'x', window->x+window->width-closeDistanceFromRight-4, window->y+(titleBarHeight/2-10)); //"X" for window close in white
    }
    else{
        graphics->putChar(color_rgb(0, 0, 0), 'x', window->x+window->width-closeDistanceFromRight-4, window->y+(titleBarHeight/2-10)); //"X" for window close in black (not hightlighted)
    }

    if((window->properties >> 2) & 1){
        graphics->fillRect(color_rgb(0, 255, 0), window->x+window->width-closeDistanceFromRight - 29, window->y+(titleBarHeight/2) - 8, 15, 16);
    }

    if((window->properties >> 1) & 1){
        graphics->drawRect(color_rgb(0, 0, 0), window->x+window->width-closeDistanceFromRight - 26, window->y+(titleBarHeight/2) - 4, 8, 8); //draw red rectangle for "X"(close)
    }
    else{
        graphics->drawRect(color_rgb(0, 0, 0), window->x+window->width-closeDistanceFromRight - 26, window->y+(titleBarHeight/2) - 3, 7, 7); //draw rect for slight minimizing symbol
        graphics->drawRect(color_rgb(0, 0, 0), window->x+window->width-closeDistanceFromRight - 24, window->y+(titleBarHeight/2) - 6, 7, 7); //draw rect for slight minimizing symbol
    }

    if((window->properties >> 3) & 1){
        graphics->fillRect(color_rgb(255, 255, 0), window->x+window->width-closeDistanceFromRight - 49, window->y+(titleBarHeight/2) - 8, 15, 16);
    }
    graphics->putChar(color_rgb(0, 0, 0), '-', window->x+window->width-closeDistanceFromRight - 45, window->y+(titleBarHeight/2-10)+1); //"-" for window minimize

    graphics->fillRect(color_rgb(255, 255, 255), window->x, window->y+titleBarHeight, window->width, window->height); //white rectangle for window content(framebuffer)
    graphics->drawRect(color_rgb(0, 0, 0), window->x, window->y+titleBarHeight, window->width, window->height);

}
