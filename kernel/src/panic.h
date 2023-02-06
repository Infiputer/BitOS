#pragma once
#include "Graphics.h"

extern Graphics* graphics;
static void SysPanic(const char* err){
    graphics->clear(0x0000ff);
    graphics->print(0xffffff, "BitOS has run into an error", 20, 20);
    graphics->print(0xffffff, err, 20, 60);
}