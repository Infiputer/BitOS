#pragma once
#include "../graphics/GraphicsHelper.h"
#include "renderPanel.h"

struct Panel
{
    const char *title;
    int32_t x;
    int32_t y;
    uint32_t width;
    uint32_t height;
    uint8_t properties; //{visible}, {full minimize highlighted}, {maximize/slight minimize hightlight}, {maximize(1) or slight minimize(0)}, {panel closed highlighted}
    RGB *framebuffer;
    uint16_t layer;
};

void InitPanels();
/*
 * Changes colors of buttons, based on mouse hover
 * @param mouseX mouse position X
 * @param mouseY mouse position Y
 */
void CheckPanelHover(uint32_t mouseX, uint32_t mouseY);
/*
 * Drags panels based on clicks and checks for events
 * @param mouseX mouse position X
 * @param mouseY mouse position Y
 */
void PanelClick(uint32_t mouseX, uint32_t mouseY);

// releases panel grab, called when mouse isn't clicked
void PanelClearPanelGrab();

// renders all the panels
void renderPanels();