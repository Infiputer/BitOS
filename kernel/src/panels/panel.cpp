#include "panel.h"
#include "../paging/PageFrameAllocator.h"

#define boxSpacing 20
#define titleBarHeight 30

uint32_t numPanels = 5;
Panel * panels;


void InitPanels(){
    panels = (Panel*)GlobalAllocator.RequestPage();
    for(uint32_t i = 0; i < numPanels; i++){
        panels[i].title = "Hello World";
        panels[i].x = i * 50 + 5;
        panels[i].y = i * 90;
        panels[i].properties = 0;
        panels[i].width=400;
        panels[i].height=50;
    }
}

void CheckPanelHover(uint32_t mouseX, uint32_t mouseY){
    for(uint32_t i = 0; i < numPanels; i++){
        if(
            mouseX < panels[i].x + panels[i].width &&
            mouseX > panels[i].x + panels[i].width - (boxSpacing * 2)
        ){
            panels[i].title = "hover";
        }
    }
}

void renderPanels(){
    for(uint32_t i = 0; i < numPanels; i++){
        renderPanel(&panels[i]);
    }
}