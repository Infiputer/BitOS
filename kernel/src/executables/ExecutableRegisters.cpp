#include "ExecutableRegisters.h"
void ExeRegisters::clear()
{
    a[0] = 0;
    b[0] = 0;
    c[0] = 0;
    d[0] = 0;
    a[1] = 0;
    b[1] = 0;
    c[1] = 0;
    d[1] = 0;
    a[2] = 0;
    b[2] = 0;
    c[2] = 0;
    d[2] = 0;
    a[3] = 0;
    b[3] = 0;
    c[3] = 0;
    d[3] = 0;
    a[4] = 0;
    b[4] = 0;
    c[4] = 0;
    d[4] = 0;
    a[5] = 0;
    b[5] = 0;
    c[5] = 0;
    d[5] = 0;
    a[6] = 0;
    b[6] = 0;
    c[6] = 0;
    d[6] = 0;
    a[7] = 0;
    b[7] = 0;
    c[7] = 0;
    d[7] = 0;
}
uint64_t ExeRegisters::getRegister(uint8_t registerNumber)
{
    uint8_t registerNumberMod = registerNumber % 15;
    uint8_t registerLetter = registerNumber / 15;
    if (registerNumberMod <= 7)
    {
        if (registerLetter == 0)
            return a[registerNumberMod];
        if (registerLetter == 1)
            return b[registerNumberMod];
        if (registerLetter == 2)
            return c[registerNumberMod];
        if (registerLetter == 3)
            return d[registerNumberMod];
    }
    else if (registerNumberMod >= 8 && registerNumberMod <= 11)
    {
        uint8_t RegA = 0;
        uint8_t RegB = 0;
        switch (registerNumberMod)
        {
        case 8:
            RegA = 0;
            RegB = 1;
            break;
        case 9:
            RegA = 2;
            RegB = 3;
            break;
        case 10:
            RegA = 4;
            RegB = 5;
            break;
        case 11:
            RegA = 6;
            RegB = 7;
            break;
        }
        if (registerLetter == 0)
            return (uint16_t)(a[RegA] << 8 | a[RegB]);
        if (registerLetter == 1)
            return (uint16_t)(b[RegA] << 8 | b[RegB]);
        if (registerLetter == 2)
            return (uint16_t)(c[RegA] << 8 | c[RegB]);
        if (registerLetter == 3)
            return (uint16_t)(d[RegA] << 8 | d[RegB]);
    }
    else if (registerNumberMod == 12 || registerNumberMod == 13)
    {
        uint8_t RegA = 0;
        uint8_t RegB = 0;
        uint8_t RegC = 0;
        uint8_t RegD = 0;
        if (registerNumberMod == 12)
        {
            RegA = 0;
            RegB = 1;
            RegC = 2;
            RegD = 3;
        }
        if (registerNumberMod == 13)
        {
            RegA = 4;
            RegB = 5;
            RegC = 6;
            RegD = 7;
        }
        if (registerLetter == 0)
            return (uint32_t)(a[RegA] << 24 | a[RegB] << 16 | a[RegC] << 8 | a[RegD]);
        if (registerLetter == 1)
            return (uint32_t)(b[RegA] << 24 | b[RegB] << 16 | b[RegC] << 8 | b[RegD]);
        if (registerLetter == 2)
            return (uint32_t)(c[RegA] << 24 | c[RegB] << 16 | c[RegC] << 8 | c[RegD]);
        if (registerLetter == 3)
            return (uint32_t)(d[RegA] << 24 | d[RegB] << 16 | d[RegC] << 8 | d[RegD]);
    }
    else if (registerNumberMod == 14)
    {
        if (registerLetter == 0)
            return (uint64_t)a[0] << 56 | (uint64_t)a[1] << 48 | (uint64_t)a[2] << 40 | (uint64_t)a[3] << 32 | (uint64_t)a[4] << 24 | (uint64_t)a[5] << 16 | (uint64_t)a[6] << 8 | (uint64_t)a[7];
        if (registerLetter == 1)
            return (uint64_t)b[0] << 56 | (uint64_t)b[1] << 48 | (uint64_t)b[2] << 40 | (uint64_t)b[3] << 32 | (uint64_t)b[4] << 24 | (uint64_t)b[5] << 16 | (uint64_t)b[6] << 8 | (uint64_t)b[7];
        if (registerLetter == 2)
            return (uint64_t)c[0] << 56 | (uint64_t)c[1] << 48 | (uint64_t)c[2] << 40 | (uint64_t)c[3] << 32 | (uint64_t)c[4] << 24 | (uint64_t)c[5] << 16 | (uint64_t)c[6] << 8 | (uint64_t)c[7];
        if (registerLetter == 3)
            return (uint64_t)d[0] << 56 | (uint64_t)d[1] << 48 | (uint64_t)d[2] << 40 | (uint64_t)d[3] << 32 | (uint64_t)d[4] << 24 | (uint64_t)d[5] << 16 | (uint64_t)d[6] << 8 | (uint64_t)d[7];
    }
    return 0;
};
uint8_t ExeRegisters::sizeBytesReg(uint8_t registerNumber)
{
    uint8_t registerNumberMod = registerNumber % 15;
    if (registerNumberMod < 7)
        return 1;
    if (registerNumberMod >= 8 && registerNumberMod <= 11)
        return 2;
    if (registerNumberMod == 12 || registerNumberMod <= 13)
        return 4;
    if (registerNumberMod == 14)
        return 8;
    return 0;
}

void ExeRegisters::setRegister(uint8_t registerNumber, uint64_t value)
{
    uint8_t registerNumberMod = registerNumber % 15;
    uint8_t registerLetter = registerNumber / 15;
    if (registerNumberMod <= 7)
    {
        if (registerLetter == 0)
            a[registerNumberMod] = (uint8_t)value;
        else if (registerLetter == 1)
            b[registerNumberMod] = (uint8_t)value;
        else if (registerLetter == 2)
            c[registerNumberMod] = (uint8_t)value;
        else if (registerLetter == 3)
            d[registerNumberMod] = (uint8_t)value;
    }
    else if (registerNumberMod == 14)
    {
        for (int i = 0; i < 7; i++)
        {
            if (registerLetter == 0)
                a[7 - i] = (uint8_t)(value >> (i * 8));
            else if (registerLetter == 1)
                b[7 - i] = (uint8_t)(value >> (i * 8));
            else if (registerLetter == 2)
                c[7 - i] = (uint8_t)(value >> (i * 8));
            else if (registerLetter == 3)
                d[7 - i] = (uint8_t)(value >> (i * 8));
        }
    }
    else if (registerNumberMod >= 8 && registerNumberMod <= 11)
    {
        uint16_t value16 = (uint16_t)value;
        if (registerLetter == 0)
        {
            a[registerNumberMod - 8] = (uint8_t)(value16 >> 8);
            a[registerNumberMod - 7] = (uint8_t)value16;
        }
        else if (registerLetter == 1)
        {
            b[registerNumberMod - 8] = (uint8_t)(value16 >> 8);
            b[registerNumberMod - 7] = (uint8_t)value16;
        }
        else if (registerLetter == 2)
        {
            c[registerNumberMod - 8] = (uint8_t)(value16 >> 8);
            c[registerNumberMod - 7] = (uint8_t)value16;
        }
        else if (registerLetter == 3)
        {
            d[registerNumberMod - 8] = (uint8_t)(value16 >> 8);
            d[registerNumberMod - 7] = (uint8_t)value16;
        }
    }
    else if (registerNumberMod == 12 || registerNumberMod == 13)
    {
        uint8_t regA = 0;
        uint8_t regB = 0;
        uint8_t regC = 0;
        uint8_t regD = 0;
        if (registerNumberMod == 12)
        {
            regA = 0;
            regB = 1;
            regC = 2;
            regD = 3;
        }
        else // registerNumberMod == 13
        {
            regA = 4;
            regB = 5;
            regC = 6;
            regD = 7;
        }
        if (registerLetter == 0)
        {
            a[regA] = (uint8_t)(value >> 24);
            a[regB] = (uint8_t)(value >> 16);
            a[regC] = (uint8_t)(value >> 8);
            a[regD] = (uint8_t)value;
        }
        else if (registerLetter == 1)
        {
            b[regA] = (uint8_t)(value >> 24);
            b[regB] = (uint8_t)(value >> 16);
            b[regC] = (uint8_t)(value >> 8);
            b[regD] = (uint8_t)value;
        }
        else if (registerLetter == 2)
        {
            c[regA] = (uint8_t)(value >> 24);
            c[regB] = (uint8_t)(value >> 16);
            c[regC] = (uint8_t)(value >> 8);
            c[regD] = (uint8_t)value;
        }
        else if (registerLetter == 3)
        {
            d[regA] = (uint8_t)(value >> 24);
            d[regB] = (uint8_t)(value >> 16);
            d[regC] = (uint8_t)(value >> 8);
            d[regD] = (uint8_t)value;
        }
    }
}