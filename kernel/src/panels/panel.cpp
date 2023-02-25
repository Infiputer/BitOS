#include "panel.h"
#include "../paging/PageFrameAllocator.h"
#include "../ToString.h"
#include "../Graphics.h"
#include "../BitOSUtilities.h"

#define boxSpacing 20
#define titleBarHeight 30

uint32_t numPanels = 5;
Panel *panels;

void InitPanels()
{
    panels = (Panel *)GlobalAllocator.RequestPage();
    for (uint32_t i = 0; i < numPanels; i++)
    {
        panels[i].title = "Hello World";
        panels[i].x = i * 50 + 5;
        panels[i].y = i * 90;
        panels[i].properties = 0;
        panels[i].width = 400;
        panels[i].height = 50;
    }
}

bool boxHover(Panel *panel, uint32_t mouseX, uint32_t mouseY, uint8_t boxNumber)
{
    return ((panel->x + panel->width - boxSpacing * boxNumber) < mouseX &&
            (panel->x + panel->width - boxSpacing * (boxNumber - 1)) > mouseX &&
            panel->y < mouseY &&
            (panel->y + titleBarHeight) > mouseY);
}

// the properties of panel {visible}, {full minimize highlighted}, {maximize/slight minimize hightlight}, {maximize(1) or slight minimize(0)}, {panel closed highlighted}
void CheckPanelHover(uint32_t mouseX, uint32_t mouseY)
{
    for (uint32_t i = 0; i < numPanels; i++)
    {

        panels[i].properties = setBit(panels[i].properties, 0, boxHover(&panels[i], mouseX, mouseY, 1)); // Close button
        panels[i].properties = setBit(panels[i].properties, 2, boxHover(&panels[i], mouseX, mouseY, 2)); // Restore Down, Maximize
        panels[i].properties = setBit(panels[i].properties, 3, boxHover(&panels[i], mouseX, mouseY, 3)); // Minimize
    }
    renderPanels();
}

void renderPanels()
{
    for (uint32_t i = 0; i < numPanels; i++)
    {
        renderPanel(&panels[i]);
    }
}