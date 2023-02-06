#include "memory.h"
void memset(void *start, uint8_t value, uint64_t num)
{
    for (uint64_t i = 0; i < num; i++)
    {
        *(uint8_t *)((uint64_t)start + i) = value;
    }
}

void *memcpy(void *dest, const void *src, uint64_t n)
{
    const unsigned char *q = (const unsigned char*)src;
    unsigned char *p = (unsigned char*)dest;

    while (n--)
        *p++ = *q++;

    return dest;
}