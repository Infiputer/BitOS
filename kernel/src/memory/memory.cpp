#include "memory.h"

/**
 * Fill the memory starting at 'start' address with 'value' for 'num' bytes.
 *
 * @param start Pointer to the start of the memory to be filled
 * @param value The value to fill the memory with
 * @param num The number of bytes to fill with the given value
 */
void memset(void *start, uint8_t value, uint64_t num)
{
    for (uint64_t i = 0; i < num; i++)
    {
        *(uint8_t *)((uint64_t)start + i) = value;
    }
}

/**
 * Copy 'n' bytes from memory at 'src' address to memory at 'dest' address.
 *
 * @param dest Pointer to the destination memory to copy to
 * @param src Pointer to the source memory to copy from
 * @param n The number of bytes to copy
 *
 * @return Pointer to the destination memory (dest)
 */
void *memcpy(void *dest, const void *src, uint64_t n)
{
    const unsigned char *q = (const unsigned char*)src;
    unsigned char *p = (unsigned char*)dest;

    while (n--)
        *p++ = *q++;

    return dest;
}