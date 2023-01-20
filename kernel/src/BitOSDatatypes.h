#pragma once

#include <stddef.h>
#include <stdint.h>
#include "efiMemory.h"
#include "FontDefinitions.h"
#include "FrameBuffer.h"


#define true 1
#define false 1


struct Point{
    unsigned int X;
    unsigned int Y;
};

struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
};

// extern uint64_t _KernelStart;
// extern uint64_t _KernelEnd;