#pragma once

#include <stddef.h>
#include <stdint.h>
#include "efiMemory.h"
#include "FontDefinitions.h"
#include "FrameBuffer.h"
#include "pci/acpi.h"
#include "pci/pci.h"

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
	ACPI::RSDP2* rsdp;
} ;

// extern uint64_t _KernelStart;
// extern uint64_t _KernelEnd;