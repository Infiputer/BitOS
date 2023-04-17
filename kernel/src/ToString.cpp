#include "ToString.h"
const char *to_string(uint64_t value)
{
    static char buffer[21]; // Enough for 20 digits + null terminator
    int i = 20;
    buffer[i--] = '\0';
    do
    {
        buffer[i--] = '0' + value % 10;
        value /= 10;
    } while (value);
    return &buffer[i + 1];
}

const char *to_string(int64_t value)
{
    static char buffer[22]; // Enough for 1 sign + 20 digits + null terminator
    int i = 21;
    buffer[i--] = '\0';
    bool negative = value < 0;
    if (negative)
        value = -value;
    do
    {
        buffer[i--] = '0' + value % 10;
        value /= 10;
    } while (value);
    if (negative)
        buffer[i--] = '-';
    return &buffer[i + 1];
}

const char *to_hstring(uint64_t value)
{
    static char buffer[17]; // Enough for 16 hex digits + null terminator
    int i = 16;
    buffer[i--] = '\0';
    do
    {
        buffer[i--] = "0123456789abcdef"[value % 16];
        value /= 16;
    } while (value);
    return &buffer[i + 1];
}

const char *to_hstring(uint32_t value)
{
    static char buffer[9]; // Enough for 8 hex digits + null terminator
    int i = 8;
    buffer[i--] = '\0';
    do
    {
        buffer[i--] = "0123456789abcdef"[value % 16];
        value /= 16;
    } while (value);
    return &buffer[i + 1];
}

const char *to_hstring(uint16_t value)
{
    static char buffer[5]; // Enough for 4 hex digits + null terminator
    int i = 4;
    buffer[i--] = '\0';
    do
    {
        buffer[i--] = "0123456789abcdef"[value % 16];
        value /= 16;
    } while (value);
    return &buffer[i + 1];
}

const char *to_hstring(uint8_t value)
{
    static char buffer[3]; // Enough for 2 hex digits + null terminator
    int i = 2;
    buffer[i--] = '\0';
    do
    {
        buffer[i--] = "0123456789abcdef"[value % 16];
        value /= 16;
    } while (value);
    return &buffer[i + 1];
}
char doubleTo_StringOutput[128];
const char *to_string(double value, uint8_t decimalPlaces)
{
    if (decimalPlaces > 20)
        decimalPlaces = 20;

    char *intPtr = (char *)to_string((int64_t)value);
    char *doublePtr = doubleTo_StringOutput;

    if (value < 0)
    {
        value *= -1;
    }

    while (*intPtr != 0)
    {
        *doublePtr = *intPtr;
        intPtr++;
        doublePtr++;
    }

    *doublePtr = '.';
    doublePtr++;

    double newValue = value - (int)value;

    for (uint8_t i = 0; i < decimalPlaces; i++)
    {
        newValue *= 10;
        *doublePtr = (int)newValue + '0';
        newValue -= (int)newValue;
        doublePtr++;
    }

    *doublePtr = 0;
    return doubleTo_StringOutput;
}

const char *to_string(double value)
{
    return to_string(value, 2);
}