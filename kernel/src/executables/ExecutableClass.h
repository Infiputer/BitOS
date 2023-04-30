// Documentation on BitOS Assembly: https://1drv.ms/w/s!AvmohCKk6gSggdUgK-VeF85_lcnv5g?e=Hobwbe
#pragma once
#include <stdint.h>
#include "../paging/PageFrameAllocator.h"
#include "ExecutableRegisters.h"
#include "../logger/logger.h"
#include "../ToString.h"

#define BYTE 1
#define WORD 2
#define DOUBLEWORD 4
#define QUADWORD 8

#define DEBUG false

#if DEBUG == true
const char * functionsStrings[] = {"ENDPRG", "NOP", "ADDRR", "ADDMM", "ADDRM", "ADDRI", "SUBRR", "SUBMM", "SUBRM", "SUBRI", "MULRR", "MULMM", "MULRM", "MULRI", "DIVRR", "DIVMM", "DIVRM", "DIVRI", "LEAMR", "LEARR", "CMPRR", "CMPRM", "CMPRI", "JE", "JG", "JL", "JNE", "JMP", "PRINT", "PRINTCHR", "SET"};
#endif

class Executable
{
public:
    size_t codeSize;

    ExeRegisters exeRegs;

    uint64_t currentCodePointer = 0;
    uint8_t *exePages[10];
    size_t exeSize;

    bool progEnd = false;

    void InitExe(size_t ExeSize)
    {
        exeSize = ExeSize;
        currentCodePointer = 0;

        exeRegs.clear();
    };

    uint32_t pageArrNum = 0;
    uint8_t cmpFlag = 2; // 0. equal; 1. less than; 2. greater than;
    bool overflowFlag = false;
    void addPage(uint8_t *page)
    {
        exePages[pageArrNum++] = page;
    }

    void cmp(uint64_t val1, uint64_t val2)
    {
        if (val1 == val2)
            cmpFlag = 0;
        else if (val1 < val1)
            cmpFlag = 1;
        else
            cmpFlag = 2;
    };

    uint64_t getExeBytes(uint64_t index, uint8_t size)
    {
        uint64_t result = 0;
        if (size == 0 || size > 8)
            return 0;
        for (uint8_t i = 0; i < size; i++)
        {
            result |= (uint64_t)(*getExeIndex(index + i)) << (((size - 1) - i) * 8);
        }
        return result;
    }

    void setExeBytes(uint64_t index, uint64_t value, uint8_t size)
    {
        if (size == 0 || size > 8)
            return; // Invalid size

        for (uint8_t i = 0; i < size; i++)
        {
            uint8_t byte = (value >> (((size - 1) - i) * 8)) & 0xFF; // Extract the i-th byte from the value
            *getExeIndex(index + i) = byte;                          // Write the byte to the executable file
        }
    }

    uint8_t *getExeIndex(uint64_t index)
    {
        return (uint8_t *)(exePages[index / 4096] + index % 4096);
    }

    void setExeIndex(uint64_t index, uint8_t value)
    {
        *(uint8_t *)(exePages[index / 4096] + index % 4096) = value;
    }

    void RunStep()
    {
        if (currentCodePointer >= exeSize || progEnd)
            return; // reached end of program
        uint8_t instruction = *(uint8_t *)getExeIndex(currentCodePointer++);

#if DEBUG == true
        log("Mem Location: ", 0, 0, 0);
        log(to_string(currentCodePointer - 1), 0, 0, 0);
        log(", Mnemonic: ", 0, 0, 0);
        log(functionsStrings[instruction]);
#endif

        if (instruction == 0x0) // End of program
            progEnd = true;
        else if (instruction == 0x01) // HALT; implement later
            asm("nop");
        // ---------------------------------------------------
        else if (instruction == 0x02) // ADD reg1 += reg2
        {
            uint8_t reg1 = exeRegs.getRegister(*getExeIndex(currentCodePointer));
            uint64_t result = reg1 + exeRegs.getRegister(*(uint8_t *)getExeIndex(currentCodePointer++));
            if (exeRegs.sizeBytesReg(reg1) != 8)
                overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg1));
            exeRegs.setRegister(reg1, result);
        }
        else if (instruction == 0x03) // ADD byte; size, mloc += mloc
        {
            uint8_t mlocSize = *getExeIndex(currentCodePointer++);

            if (mlocSize == 0 || mlocSize > 8)
                return;

            uint64_t mloc1 = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;

            uint64_t mloc2 = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;

            uint64_t result = getExeBytes(mloc1, mlocSize) + getExeBytes(mloc2, mlocSize);
            overflowFlag = result >= pow(256, mlocSize); // can't go higher than 256 ^ 1

            setExeBytes(mloc1, result, mlocSize);
        }
        else if (instruction == 0x04) // ADD byte; size, reg += mloc
        {
            uint8_t mlocSize = *getExeIndex(currentCodePointer++);
            if (mlocSize == 0 || mlocSize > 8)
                return;
            uint8_t reg = *getExeIndex(currentCodePointer++);
            uint64_t result = exeRegs.getRegister(reg) + getExeBytes(getExeBytes(currentCodePointer, 8), mlocSize);
            currentCodePointer += 8;
            overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg));
            exeRegs.setRegister(reg, result);
        }
        else if (instruction == 0x05) // ADD reg -= int
        {
            uint8_t reg = *getExeIndex(currentCodePointer++);
            uint64_t result = exeRegs.getRegister(reg) + getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;
            overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg));
            exeRegs.setRegister(reg, result);
        }
        // ---------------------------------------------------
        else if (instruction == 0x06) // SUBTRACT reg1 -= reg2
        {
            uint8_t reg1 = exeRegs.getRegister(*getExeIndex(currentCodePointer));
            uint64_t result = reg1 - exeRegs.getRegister(*(uint8_t *)getExeIndex(currentCodePointer++));
            if (exeRegs.sizeBytesReg(reg1) != 8)
                overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg1));
            exeRegs.setRegister(reg1, result);
        }
        else if (instruction == 0x07) // SUBTRACT; size, mloc1 -= mloc2
        {
            uint8_t mlocSize = *getExeIndex(currentCodePointer++);

            if (mlocSize == 0 || mlocSize > 8)
                return;

            uint64_t mloc1 = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;

            uint64_t mloc2 = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;

            uint64_t result = getExeBytes(mloc1, mlocSize) - getExeBytes(mloc2, mlocSize);
            overflowFlag = result >= pow(256, mlocSize); // can't go higher than 256 ^ 1

            setExeBytes(mloc1, result, mlocSize);
        }
        else if (instruction == 0x08) // SUBTRACT; size, reg -= mloc
        {
            uint8_t mlocSize = *getExeIndex(currentCodePointer++);
            if (mlocSize == 0 || mlocSize > 8)
                return;
            uint8_t reg = *getExeIndex(currentCodePointer++);
            uint64_t result = exeRegs.getRegister(reg) - getExeBytes(getExeBytes(currentCodePointer, 8), mlocSize);
            currentCodePointer += 8;
            overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg));
            exeRegs.setRegister(reg, result);
        }
        else if (instruction == 0x09) // SUBTRACT reg -= int
        {
            uint8_t reg = *getExeIndex(currentCodePointer++);
            uint64_t result = exeRegs.getRegister(reg) - getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;
            overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg));
            exeRegs.setRegister(reg, result);
        }
        // ---------------------------------------------------
        else if (instruction == 0x0A) // MULTIPLY reg1 *= reg2
        {
            uint8_t reg1 = exeRegs.getRegister(*getExeIndex(currentCodePointer));
            uint64_t result = reg1 * exeRegs.getRegister(*(uint8_t *)getExeIndex(currentCodePointer++));
            if (exeRegs.sizeBytesReg(reg1) != 8)
                overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg1));
            exeRegs.setRegister(reg1, result);
        }
        else if (instruction == 0x0B) // MULTIPLY; size, mloc1 *= mloc2
        {
            uint8_t mlocSize = *getExeIndex(currentCodePointer++);

            if (mlocSize == 0 || mlocSize > 8)
                return;

            uint64_t mloc1 = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;

            uint64_t mloc2 = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;

            uint64_t result = getExeBytes(mloc1, mlocSize) * getExeBytes(mloc2, mlocSize);
            overflowFlag = result >= pow(256, mlocSize); // can't go higher than 256 ^ 1

            setExeBytes(mloc1, result, mlocSize);
        }
        else if (instruction == 0x0C) // MULTIPLY; size, reg *= mloc
        {
            uint8_t mlocSize = *getExeIndex(currentCodePointer++);
            if (mlocSize == 0 || mlocSize > 8)
                return;
            uint8_t reg = *getExeIndex(currentCodePointer++);
            uint64_t result = exeRegs.getRegister(reg) * getExeBytes(getExeBytes(currentCodePointer, 8), mlocSize);
            currentCodePointer += 8;
            overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg));
            exeRegs.setRegister(reg, result);
        }
        else if (instruction == 0x0D) // MULITPLY reg *= int
        {
            uint8_t reg = *getExeIndex(currentCodePointer++);
            uint64_t result = exeRegs.getRegister(reg) * getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;
            overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg));
            exeRegs.setRegister(reg, result);
        }
        // ---------------------------------------------------
        else if (instruction == 0x0E) // DIVIDE reg1 /= reg2
        {
            uint8_t reg1 = exeRegs.getRegister(*getExeIndex(currentCodePointer));
            uint64_t result = reg1 / exeRegs.getRegister(*(uint8_t *)getExeIndex(currentCodePointer++));
            if (exeRegs.sizeBytesReg(reg1) != 8)
                overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg1));
            exeRegs.setRegister(reg1, result);
        }
        else if (instruction == 0x0F) // DIVIDE; size, mloc1 *= mloc2
        {
            uint8_t mlocSize = *getExeIndex(currentCodePointer++);

            if (mlocSize == 0 || mlocSize > 8)
                return;

            uint64_t mloc1 = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;

            uint64_t mloc2 = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;

            uint64_t result = getExeBytes(mloc1, mlocSize) / getExeBytes(mloc2, mlocSize);
            overflowFlag = result >= pow(256, mlocSize); // can't go higher than 256 ^ 1

            setExeBytes(mloc1, result, mlocSize);
        }
        else if (instruction == 0x10) // DIVIDE; size, reg /= mloc
        {
            uint8_t mlocSize = *getExeIndex(currentCodePointer++);
            if (mlocSize == 0 || mlocSize > 8)
                return;
            uint8_t reg = *getExeIndex(currentCodePointer++);
            uint64_t result = exeRegs.getRegister(reg) / getExeBytes(getExeBytes(currentCodePointer, 8), mlocSize);
            currentCodePointer += 8;
            overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg));
            exeRegs.setRegister(reg, result);
        }
        else if (instruction == 0x11) // DIVIDE reg /= int
        {
            uint8_t reg = *getExeIndex(currentCodePointer++);
            uint64_t result = exeRegs.getRegister(reg) / getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;
            overflowFlag = result >= pow(256, exeRegs.sizeBytesReg(reg));
            exeRegs.setRegister(reg, result);
        }
        // ---------------------------------------------------
        else if (instruction == 0x12) // LEA mloc reg
        {
            uint64_t mloc = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;
            uint8_t reg = *getExeIndex(currentCodePointer++);
            exeRegs.setRegister(reg, getExeBytes(mloc, exeRegs.sizeBytesReg(reg)));
        }
        else if (instruction == 0x13) // LEA [reg] reg
        {
            uint64_t mloc = exeRegs.getRegister(*getExeIndex(currentCodePointer++));
            uint8_t reg = *getExeIndex(currentCodePointer++);
            exeRegs.setRegister(reg, getExeBytes(mloc, exeRegs.sizeBytesReg(reg)));
        }
        // ---------------------------------------------------
        else if (instruction == 0x14) // CMPRR
        {
            uint64_t reg1Value = exeRegs.getRegister(*getExeIndex(currentCodePointer++));
            uint64_t reg2Value = exeRegs.getRegister(*getExeIndex(currentCodePointer++));
            cmp(reg1Value, reg2Value);
        }
        else if (instruction == 0x16)
        {
            uint64_t regValue = exeRegs.getRegister(*getExeIndex(currentCodePointer++));
            uint64_t cmpInt = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;
            cmp(regValue, cmpInt);
        }
        // ---------------------------------------------------
        else if (instruction == 0x17)
        { // JUMP IF EQUAL
            uint64_t jmpMloc = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;
            if (cmpFlag == 0)
            {
                currentCodePointer = jmpMloc;
#if DEBUG == true
                log("JE to ", 0, 0, 0);
                log(to_string(currentCodePointer));
#endif
            }
        }
        else if (instruction == 0x1A) // JUMP NO EQUAL
        {
            uint64_t jmpMloc = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;
            if (cmpFlag != 0)
                currentCodePointer = jmpMloc;
        }
        else if (instruction == 0x1B)
        { // JUMP [no condition]
            uint64_t jmpMloc = getExeBytes(currentCodePointer, 8);
            currentCodePointer = jmpMloc;
#if DEBUG == true
            log("JMP to ", 0, 0, 0);
            log(to_string(currentCodePointer));
#endif
        }
        // ---------------------------------------------------
        else if (instruction == 0x1C)
        {
            char charAsStr[] = {(int8_t)(uint8_t)exeRegs.getRegister(0), 0}; // Print A0
            log(charAsStr, LOG_LIGHT_BLUE, 0, 0);
        }
        else if (instruction == 0x1D)
        {
            char charAsStr[] = {(int8_t)(uint8_t)*getExeIndex(currentCodePointer++), 0};
            log(charAsStr, 0, 0, 0);
        }
        // ---------------------------------------------------
        else if (instruction == 0x1E) // SET reg int[64bit]
        {
            uint8_t reg = *getExeIndex(currentCodePointer++);
            uint64_t value = getExeBytes(currentCodePointer, 8);
            currentCodePointer += 8;
            exeRegs.setRegister(reg, value);
        }
        else
        {
            log("Unknown instruction ", LOG_RED, 0, 0);
            log(to_hstring((uint64_t)instruction), LOG_RED);
        }
    }
};
