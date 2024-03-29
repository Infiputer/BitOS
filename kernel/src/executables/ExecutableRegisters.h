#pragma once
#include <stdint.h>
struct ExeRegisters
{
    uint8_t a[8];
    uint8_t b[8];
    uint8_t c[8];
    uint8_t d[8];

    void clear();
    uint64_t getRegister(uint8_t registerNumber);
    void setRegister(uint8_t registerNumber, uint64_t value);
    uint8_t sizeBytesReg(uint8_t registerNumber);
};

/* STRUCTURE OF REGISTERS
┌────────────────────────────────────────────────────────────────┐
│                          14 (64 bit)                           │
└────────────────────────────────────────────────────────────────┘
┌───────────────────────────────┐┌───────────────────────────────┐
│            12 (32 bit)        ││          13 (32 bit)          │
└───────────────────────────────┘└───────────────────────────────┘
┌───────────────┐┌──────────────┐┌──────────────┐┌───────────────┐
│  8 (16 bit)   ││  9 (16 bit)  ││  10 (16 bit) ││  11 (16 bit)  │
└───────────────┘└──────────────┘└──────────────┘└───────────────┘
┌───────┐┌──────┐┌─────┐┌───────┐┌───────┐┌──────┐┌──────┐┌──────┐
│   0   ││  1   ││  2  ││   3   ││   4   ││  5   ││   6  ││  7   │
└───────┘└──────┘└─────┘└───────┘└───────┘└──────┘└──────┘└──────┘
            0 - 7 are 8 bit
*/