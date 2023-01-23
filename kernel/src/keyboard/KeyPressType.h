#pragma once
#include <stddef.h>
struct KeyPress
{
    char key;          // ascii: a, b, c or numbers: 0, 1, 2
    char keyType;      // type of key such as 0x0: control char, 0x3: arrow key
    uint16_t timeHeld; // time key is pressed down
};