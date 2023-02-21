#pragma once
#include <stdint.h>
#include "../BitOSUtilities.h"
#include "../GraphicsHelper.h"
#include "../Graphics.h"
#include "panel.h"

#define titleBarHeight 30
#define closeDistanceFromRight 25 // distance from left corner of the X, to the right of the panel
#define boxSize 16
#define boxSpacing 20

void renderPanel(struct Panel* panel); 

