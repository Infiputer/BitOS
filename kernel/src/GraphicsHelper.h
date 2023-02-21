#pragma once
#include <stdint.h>
#define color_rgb(r, g, b) ((unsigned int)((unsigned int)0x00010000*r+(unsigned int)0x00000100*g+(unsigned int)0x00000001*b))
struct RGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};
