#include <stdint.h>
#include <cstring>

#define color_rgba(r, g, b, a) ((unsigned int)((unsigned int)0x01000000*a+(unsigned int)0x00010000*r+(unsigned int)0x00000100*g+(unsigned int)0x00000001*b))

Graphics* graphics;

struct Window{
    char title[50];
    uint64_t x;
    uint64_t y;
    uint64_t width;
    uint64_t height;
};

#define titleBarHeight 30
#define closeDistanceFromRight 17

void renderWindow(Window* window){
    graphics->fillRect(color_rgba(59, 195, 255, 255), window->x, window->y, window->width, titleBarHeight);
    graphics->drawRect(color_rgba(0, 0, 0, 255), window->x, window->y, window->width, titleBarHeight);
    graphics->print(color_rgba(255, 255, 255, 255), window->title, window->x+window->width/2-(strlen(window->title)*4), window->y+(titleBarHeight/2-10));
    graphics->fillCircle(color_rgba(255, 0, 0, 255), window->x+window->width-closeDistanceFromRight, window->y+(titleBarHeight/2), 10); //draw red circle for "X"(close)
    graphics->putChar(color_rgba(255, 255, 255, 255), 'x', window->x+window->width-closeDistanceFromRight-4, window->y+(titleBarHeight/2-10));

    graphics->fillRect(color_rgba(255, 255, 255, 255), window->x, window->y+titleBarHeight, window->width, window->height); //white rectangle for window content(framebuffer)
    graphics->drawRect(color_rgba(0, 0, 0, 0), window->x, window->y+titleBarHeight, window->width, window->height);
    graphics->render();
}
