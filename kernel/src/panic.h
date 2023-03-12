#pragma once
#include "graphics/Graphics.h"

/**
 * Shows a panic screen with error
 * @param error the error
 */
static void SysPanic(const char *error)
{
    graphics->clear(0x0000ff);
    graphics->print(0xffffff, "BitOS has run into an error", 20, 20);
    graphics->print(0xffffff, error, 20, 60);
    graphics->render();
}