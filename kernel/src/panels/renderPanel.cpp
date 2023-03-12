#include "renderPanel.h"
void renderPanel(Panel *panel)
{
    graphics->fillRect(color_rgb(59, 195, 255), panel->x, panel->y, panel->width, titleBarHeight);
    graphics->drawRect(color_rgb(0, 0, 0), panel->x, panel->y, panel->width, titleBarHeight);

    graphics->print(color_rgb(0, 0, 0), panel->title, panel->x + panel->width / 2 - (strlen(panel->title) * 4) - 1, panel->y + (titleBarHeight / 2 - 10));     // prints text in black for shadow effect to the left of normal
    graphics->print(color_rgb(0, 0, 0), panel->title, panel->x + panel->width / 2 - (strlen(panel->title) * 4) + 1, panel->y + (titleBarHeight / 2 - 10));     // prints text in black for shadow effect to the left of normal
    graphics->print(color_rgb(0, 0, 0), panel->title, panel->x + panel->width / 2 - (strlen(panel->title) * 4) + 1, panel->y + (titleBarHeight / 2 - 10) + 1); // prints text in black for shadow effect to the right
    graphics->print(color_rgb(0, 0, 0), panel->title, panel->x + panel->width / 2 - (strlen(panel->title) * 4), panel->y + (titleBarHeight / 2 - 10) - 1);     // prints text in black for shadow effect above the normal text
    graphics->print(color_rgb(0, 0, 0), panel->title, panel->x + panel->width / 2 - (strlen(panel->title) * 4), panel->y + (titleBarHeight / 2 - 10) + 1);     // prints text in black for shadow effect below

    graphics->print(color_rgb(255, 255, 255), panel->title, panel->x + panel->width / 2 - (strlen(panel->title) * 4), panel->y + (titleBarHeight / 2 - 10)); // prints text in white

    if ((panel->properties >> 0) & 1)
    {
        graphics->fillRect(color_rgb(255, 0, 0), panel->x + panel->width - closeDistanceFromRight, panel->y + (titleBarHeight / 2) - 8, boxSize, boxSize); // draw red rectangle for "X"(close)
        graphics->putChar(color_rgb(255, 255, 255), 'x', panel->x + panel->width - closeDistanceFromRight + 4, panel->y + (titleBarHeight / 2 - 10));      //"X" for panel close in white
    }
    else
    {
        graphics->putChar(color_rgb(0, 0, 0), 'x', panel->x + panel->width - closeDistanceFromRight + 4, panel->y + (titleBarHeight / 2 - 10)); //"X" for panel close in black (not hightlighted)
    }

    if ((panel->properties >> 2) & 1)
    {
        graphics->fillRect(color_rgb(0, 255, 0), panel->x + panel->width - closeDistanceFromRight - boxSpacing, panel->y + (titleBarHeight / 2) - 8, 15, 16);
    }

    if ((panel->properties >> 1) & 1)
    {
        graphics->drawRect(color_rgb(0, 0, 0), panel->x + panel->width - closeDistanceFromRight - boxSpacing + 3, panel->y + (titleBarHeight / 2) - 4, 8, 8); // draw red rectangle for "X"(close)
    }
    else
    {
        graphics->drawRect(color_rgb(0, 0, 0), panel->x + panel->width - closeDistanceFromRight - boxSpacing + 3, panel->y + (titleBarHeight / 2) - 3, 7, 7); // draw rect for slight minimizing symbol
        graphics->drawRect(color_rgb(0, 0, 0), panel->x + panel->width - closeDistanceFromRight - boxSpacing + 5, panel->y + (titleBarHeight / 2) - 6, 7, 7); // draw rect for slight minimizing symbol
    }

    if ((panel->properties >> 3) & 1)
    {
        graphics->fillRect(color_rgb(255, 255, 0), panel->x + panel->width - closeDistanceFromRight - boxSpacing * 2, panel->y + (titleBarHeight / 2) - 8, 15, 16);
    }
    graphics->putChar(color_rgb(0, 0, 0), '-', panel->x + panel->width - closeDistanceFromRight - boxSpacing * 2 + 3, panel->y + (titleBarHeight / 2 - 10) + 1); //"-" for panel minimize

    graphics->fillRect(color_rgb(255, 255, 255), panel->x, panel->y + titleBarHeight, panel->width, panel->height); // white rectangle for panel content(framebuffer)
    graphics->drawRect(color_rgb(0, 0, 0), panel->x, panel->y + titleBarHeight, panel->width, panel->height);
}
