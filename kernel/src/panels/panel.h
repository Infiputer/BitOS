#pragma once
#include "../GraphicsHelper.h"
#include "renderPanel.h"

struct Panel{
    const char * title;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    uint8_t properties; //{visible}, {full minimize highlighted}, {maximize/slight minimize hightlight}, {maximize(1) or slight minimize(0)}, {panel closed highlighted}
    RGB* framebuffer;
    uint16_t layer;
};

void InitPanels();
void CheckPanelHover(uint32_t mouseX, uint32_t mouseY);
void renderPanels();