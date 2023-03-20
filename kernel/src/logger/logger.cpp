#include "logger.h"
#include "../paging/PageFrameAllocator.h"
#include "../memory/memory.h"
#include "../graphics/Graphics.h"
#include "../graphics/GraphicsHelper.h"

uint32_t LogSize = 2000;
uint32_t currentLogPosition = 0;

char *logText = nullptr;

void InitLog()
{
    if (logText != nullptr)
        return;
    logText = (char *)GlobalAllocator.RequestPage();
};

#define LOG_RGB_LIGHT_RED    color_rgb(255, 77, 77)
#define LOG_RGB_LIGHT_ORANGE color_rgb(255, 195, 77)
#define LOG_RGB_LIGHT_YELLOW color_rgb(255, 255, 77)
#define LOG_RGB_LIGHT_GREEN  color_rgb(166, 255, 77)
#define LOG_RGB_LIGHT_BLUE   color_rgb(77, 195, 255)
#define LOG_RGB_LIGHT_PURPLE color_rgb(229, 102, 255)
#define LOG_RGB_LIGHT_BLACK  color_rgb(150, 150, 150)
#define LOG_RGB_LIGHT_BROWN  color_rgb(204, 136, 0)
#define LOG_RGB_RED          color_rgb(255, 0, 0)
#define LOG_RGB_ORANGE       color_rgb(255, 179, 25)
#define LOG_RGB_YELLOW       color_rgb(255, 255, 25)
#define LOG_RGB_GREEN        color_rgb(43, 255, 0)
#define LOG_RGB_BLUE         color_rgb(0, 128, 255)
#define LOG_RGB_PURPLE       color_rgb(230, 0, 115)
#define LOG_RGB_WHITE        color_rgb(255, 255, 255)
#define LOG_RGB_BLACK        color_rgb(0, 0, 0)
#define LOG_RGB_BROWN        color_rgb(102, 51, 0)
#define LOG_RGB_DARK_RED     color_rgb(220, 0, 0)
#define LOG_RGB_DARK_ORANGE  color_rgb(230, 191, 0)
#define LOG_RGB_DARK_YELLOW  color_rgb(204, 204, 0)
#define LOG_RGB_DARK_GREEN   color_rgb(30, 179, 0)
#define LOG_RGB_DARK_BLUE    color_rgb(0, 0, 204)
#define LOG_RGB_DARK_PURPLE  color_rgb(204, 0, 204)
#define LOG_RGB_DARK_BROWN   color_rgb(102, 85, 0)

void log(const char *msg, uint8_t fgcolor, uint8_t bgcolor, char end)
{
    if(fgcolor == 0)
        fgcolor = LOG_WHITE;
    if(bgcolor == 0)
        bgcolor = LOG_BLACK;
    if(fgcolor<=65 || fgcolor >= 88 || bgcolor<=65 || bgcolor >= 88)
        return;
    const unsigned char *msgptr = (const unsigned char *)msg;
    logText[currentLogPosition] = 1; // start of color header
    logText[currentLogPosition + 1] = fgcolor; // make 1 into A by adding 64
    logText[currentLogPosition + 2] = bgcolor;
    currentLogPosition += 3;
    while (*msgptr != '\0')
    {
        logText[currentLogPosition] = *msgptr;
        currentLogPosition++;
        msgptr++;
    }
    if(end != 0){
        logText[currentLogPosition] = '\n';
        currentLogPosition++;
    }
    if(currentLogPosition > LogSize){
        currentLogPosition = 0;
    }
    showLog();
};

uint64_t logColortoRGB(uint8_t color)
{
    switch (color)
    {
    case 65:
        return LOG_RGB_LIGHT_RED;
    case 66:
        return LOG_RGB_LIGHT_ORANGE;
    case 67:
        return LOG_RGB_LIGHT_YELLOW;
    case 68:
        return LOG_RGB_LIGHT_GREEN;
    case 69:
        return LOG_RGB_LIGHT_BLUE;
    case 70:
        return LOG_RGB_LIGHT_PURPLE;
    case 71:
        return LOG_RGB_LIGHT_BLACK;
    case 72:
        return LOG_RGB_LIGHT_BROWN;
    case 73:
        return LOG_RGB_RED;
    case 74:
        return LOG_RGB_ORANGE;
    case 75:
        return LOG_RGB_YELLOW;
    case 76:
        return LOG_RGB_GREEN;
    case 77:
        return LOG_RGB_BLUE;
    case 78:
        return LOG_RGB_PURPLE;
    case 79:
        return LOG_RGB_WHITE;
    case 80:
        return LOG_RGB_BLACK;
    case 81:
        return LOG_RGB_BROWN;
    case 82:
        return LOG_RGB_DARK_RED;
    case 83:
        return LOG_RGB_DARK_ORANGE;
    case 84:
        return LOG_RGB_DARK_YELLOW;
    case 85:
        return LOG_RGB_DARK_GREEN;
    case 86:
        return LOG_RGB_DARK_BLUE;
    case 87:
        return LOG_RGB_DARK_PURPLE;
    case 88:
        return LOG_RGB_DARK_BROWN;
    }
    return color_rgb(0, 0, 0);
}

void showLog()
{
    graphics->clear(0);
    uint32_t logPosX = 0;
    uint32_t logPosY = 0;
    uint32_t currentfg = logColortoRGB(logText[1]);
    uint32_t currentbg = logColortoRGB(logText[2]);
    for (uint32_t i = 3; i < currentLogPosition; i++)
    {
        if (logText[i] == 1){ // 1 = SOH (START OF COLOR HEADER)
            currentfg = logColortoRGB(logText[i+1]);
            currentbg = logColortoRGB(logText[i+2]);
            i+=3;
        }
        if (logText[i] == '\n')
        {
            logPosX = 0;
            logPosY += 20;
            continue;
        }
        graphics->fillRect(currentbg, logPosX, logPosY, 8, 20);
        graphics->putChar(currentfg, logText[i], logPosX, logPosY);
        logPosX += 8;
    }
    graphics->render();
}