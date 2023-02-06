#pragma once
#include <stdint.h>
void memset(void *start, uint8_t value, uint64_t num);
void *memcpy(void *dest, const void *src, uint64_t n);