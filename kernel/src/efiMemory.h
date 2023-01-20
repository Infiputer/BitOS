#pragma once
#include <stddef.h>
#include <stdint.h>

#include "FrameBuffer.h"
#include "FontDefinitions.h"

// const char* EFI_MEMORY_TYPE_STRINGS[] {
//     "EfiReservedMemoryType",
//     "EfiLoaderCode",
//     "EfiLoaderData",
//     "EfiBootServicesCode",
//     "EfiBootServicesData",
//     "EfiRuntimeServicesCode",
//     "EfiRuntimeServicesData",
//     "EfiConventionalMemory",
//     "EfiUnusableMemory",
//     "EfiACPIReclaimMemory",
//     "EfiACPIMemoryNVS",
//     "EfiMemoryMappedIO",
//     "EfiMemoryMappedIOPortSpace",
//     "EfiPalCode",
// };

struct EFI_MEMORY_DESCRIPTOR {
    uint32_t type;
    void* physAddr;
    void* virtAddr; 
    uint64_t numPages;
    uint64_t attribs;
};

static uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize){

    static uint64_t memorySizeBytes = 0;
    if (memorySizeBytes > 0) return memorySizeBytes;

    for (int i = 0; i < mMapEntries; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        memorySizeBytes += desc->numPages * 4096;
    }

    return memorySizeBytes;

}

static void memset(void* start, uint8_t value, uint64_t num){
    for (uint64_t i = 0; i < num; i++){
        *(uint8_t*)((uint64_t)start + i) = value;
    }
}

// void *memcpy(void *dest, const void *src, uint64_t n)
// {
//     const unsigned char *q = (const unsigned char*)src;
//     unsigned char *p = (unsigned char*)dest;

//     while (n--)
//         *p++ = *q++;

//     return dest;
// }
