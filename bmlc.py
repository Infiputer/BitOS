# Bit OS Machine Langauge Compiler

import sys
from datetime import datetime

# OP Code,Mnemonic,Op1,Op2,Op3
# 0x00,ENDPRG
# 0x01,NOP
# 0x02,ADDRR,reg,reg
# 0x03,ADDMM,size[uint8_t],mloc,mloc
# 0x04,ADDRM,size[uint8_t],reg,mloc
# 0x05,ADDRI,reg,int[uint64_t]
# 0x06,SUBRR,reg,reg
# 0x07,SUBMM,size[uint8_t],mloc,mloc
# 0x08,SUBRM,size[uint8_t],reg,mloc
# 0x09,SUBRI,reg,int[uint64_t]
# 0x0A,MULRR,reg,reg
# 0x0B,MULMM,size[uint8_t],mloc,mloc
# 0x0C,MULRM,size[uint8_t],reg,mloc
# 0x0D,MULRI,reg,int[uint64_t]
# 0x0E,DIVRR,reg,reg
# 0x0F,DIVMM,size[uint8_t],mloc,mloc
# 0x10,DIVRM,size[uint8_t],reg,mloc
# 0x11,DIVRI,reg,int[uint64_t]
# 0x12,LEAMR,mloc,reg
# 0x13,LEARR,[reg],reg
# 0x14,CMPRR,reg,reg
# 0x15,CMPRM,reg,mloc
# 0x16,CMPRI,reg,int[uint64_t]
# 0x17,JE,mloc
# 0x18,JG,mloc
# 0x19,JL,mloc
# 0x1A,JNE,mloc
# 0x1B,JMP,mloc
# 0xFF,SYSCALL,int[uint16_t]
functions = {
    'ENDPRG': {
        'opcode': 0x0,
        'parameters': []
    },
    'NOP': {
        'opcode': 0x1,
        'parameters': []
    },
    'ADDRR': {
        'opcode': 0x2,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'reg', 'size': 'any'}
        ]
    },
    'ADDMM': {
        'opcode': 0x3,
        'parameters': [
            {'type': 'int', 'size': '1'},
            {'type': 'mloc', 'size': 'any'},
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'ADDRM': {
        'opcode': 0x4,
        'parameters': [
            {'type': 'int', 'size': '1'},
            {'type': 'reg', 'size': 'any'},
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'ADDRI': {
        'opcode': 0x5,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'int', 'size': '8'}
        ]
    },
    'SUBRR': {
        'opcode': 0x6,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'reg', 'size': 'any'}
        ]
    },
    'SUBMM': {
        'opcode': 0x7,
        'parameters': [
            {'type': 'int', 'size': '1'},
            {'type': 'mloc', 'size': 'any'},
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'SUBRM': {
        'opcode': 0x8,
        'parameters': [
            {'type': 'int', 'size': '1'},
            {'type': 'reg', 'size': 'any'},
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'SUBRI': {
        'opcode': 0x9,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'int', 'size': '8'}
        ]
    },
    'MULRR': {
        'opcode': 0xa,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'reg', 'size': 'any'}
        ]
    },
    'MULMM': {
        'opcode': 0xb,
        'parameters': [
            {'type': 'int', 'size': '1'},
            {'type': 'mloc', 'size': 'any'},
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'MULRM': {
        'opcode': 0xc,
        'parameters': [
            {'type': 'int', 'size': '1'},
            {'type': 'reg', 'size': 'any'},
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'MULRI': {
        'opcode': 0xd,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'int', 'size': '8'}
        ]
    },
    'DIVRR': {
        'opcode': 0xe,
        'parameters': [
            {'type': 'int', 'size': '1'},
            {'type': 'mloc', 'size': 'any'},
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'DIVMM': {
        'opcode': 0xf,
        'parameters': [
            {'type': 'int', 'size': '1'},
            {'type': 'mloc', 'size': 'any'},
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'DIVRM': {
        'opcode': 0x10,
        'parameters': [
            {'type': 'int', 'size': '1'},
            {'type': 'reg', 'size': 'any'},
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'DIVRI': {
        'opcode': 0x11,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'int', 'size': '8'}
        ]
    },
    'LEAMR': {
        'opcode': 0x12,
        'parameters': [
            {'type': 'mloc', 'size': 'any'},
            {'type': 'reg', 'size': 'any'}
        ]
    },
    'LEARR': {
        'opcode': 0x13,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'reg', 'size': 'any'}
        ]
    },
    'CMPRR': {
        'opcode': 0x14,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'reg', 'size': 'any'}
        ]
    },
    'CMPRM': {
        'opcode': 0x15,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'CMPRI': {
        'opcode': 0x16,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'int', 'size': '8'}
        ]
    },
    'JE': {
        'opcode': 0x17,
        'parameters': [
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'JG': {
        'opcode': 0x18,
        'parameters': [
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'JL': {
        'opcode': 0x19,
        'parameters': [
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'JNE': {
        'opcode': 0x1A,
        'parameters': [
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'JMP': {
        'opcode': 0x1B,
        'parameters': [
            {'type': 'mloc', 'size': 'any'}
        ]
    },
    'PRINT': {
        'opcode': 0x1C,
        'parameters': []
    },
    'PRINTCHR': {
        'opcode': 0x1D,
        'parameters': [
            {'type': 'int', 'size': '1'}
        ]
    },
    'SET': {
        'opcode': 0x1E,
        'parameters': [
            {'type': 'reg', 'size': 'any'},
            {'type': 'int', 'size': '8'}
        ]
    }
}
registers = {
    1: [
        'A0', 'A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7',
        'B0', 'B1', 'B2', 'B3', 'B4', 'B5', 'B6', 'B7',
        'C0', 'C1', 'C2', 'C3', 'C4', 'C5', 'C6', 'C7',
        'D0', 'D1', 'D2', 'D3', 'D4', 'D5', 'D6', 'D7',
    ],
    2: [
        'A8', 'A9', 'A10', 'A11',
        'B8', 'B9', 'B10', 'B11',
        'C8', 'C9', 'C10', 'C11',
        'D8', 'D9', 'D10', 'D11',
    ],
    4: [
        'A12', 'A13',
        'B12', 'B13',
        'C12', 'C13',
        'D12', 'D13'
    ],
    8: [
        'A14',
        'B14',
        'C14',
        'D14'
    ]
}


def registerToByte(reg: str):
    if reg[0] == 'A':
        letter = 0
    elif reg[0] == 'B':
        letter = 1
    elif reg[0] == 'C':
        letter = 2
    elif reg[0] == 'D':
        letter = 3
    number = int(reg[1:])
    return 15 * letter + number


def numToArray(size: int, number: int):
    arr = []
    for i in range(size):
        arr.append(0)
    for i in range(size):
        arr[size - 1 - i] = number & 0xFF
        number >>= 8
    return arr


def toInt(num: str):
    if num.startswith("0x"):
        return int(num[2:], 16)
    elif num.endswith("h"):
        return int(num[:-1], 16)
    elif len(num) == 3 and num.startswith("'") and num.endswith("'"):
        return ord(num[1])
    else:
        return int(num)
    
def bytesToHumanReadable(bytes):
    units = ['bytes', 'KB', 'MB', 'GB', 'TB']
    index = 0
    size = bytes
    
    while size >= 1024 and index < 4:
        size /= 1024
        index += 1
    
    result = "{} {}".format(round(size, 1), units[index])
    return result

def getCurrentTimeAsString():
    now = datetime.now()
    return now.strftime("%Y-%m-%d, %l:%M %p")

if len(sys.argv) < 2:
    print("Usage: python bmlc.py <file_name>")
    exit(1)
with open(sys.argv[1], 'r') as f:
    code = f.read()

codeLines = code.split('\n')

mlocLocations = {}

rawBytes = []

codeBytesNewlines = []

for line in codeLines:
    line = line.strip()
    if not line:  # line is empty
        continue
    if ' ' in line:
        mnemonicEndIndex = line.index(' ')
    else:
        mnemonicEndIndex = len(line)
    mnemonic = line[0:mnemonicEndIndex]

    parameters = line[mnemonicEndIndex:].split(',')
    parameters = [
        parameter.strip() for parameter in parameters if parameter.strip() != '']

    if mnemonic.startswith("#"):
        pass
    elif mnemonic == "DB":
        for i in parameters:
            rawBytes.append(toInt(i))
    elif mnemonic == "DBT":
        num = toInt(parameters[1])
        repeat = toInt(parameters[0])
        for i in range(0, repeat):
            rawBytes.append(num)
    elif mnemonic[0] == '$':
        mlocLocations[mnemonic] = len(rawBytes)
        codeBytesNewlines.append(len(rawBytes)-1)
    else:
        if mnemonic not in functions:
            exit('Unknown mnemonic ' + mnemonic)

        if len(functions[mnemonic]['parameters']) != len(parameters):
            exit(mnemonic + ' requires ' +
                 str(len(functions[mnemonic]['parameters'])) + ' parameters, given ' +
                 str(len(parameters))
                 )

        rawBytes.append(functions[mnemonic]['opcode'])

        for i, parameter in enumerate(parameters):
            # print('\t', parameter, end=' ')
            # print('type', functions[mnemonic]['parameters'][i]['type'])
            if functions[mnemonic]['parameters'][i]['type'] == 'int':
                if parameter[0] == '$':
                    rawBytes.append(parameter)
                    rawBytes += [0] * 7
                else:
                    rawBytes += numToArray(
                        int(functions[mnemonic]['parameters'][i]['size']),
                        toInt(parameter)
                    )
            elif functions[mnemonic]['parameters'][i]['type'] == 'mloc':
                if parameter[0] == '$':
                    rawBytes.append(parameter)
                    rawBytes += [0] * 7
                else:
                    rawBytes += numToArray(
                        8,  # 64-bit system; 8 byte pointers
                        toInt(parameter)
                    )
            elif functions[mnemonic]['parameters'][i]['type'] == 'reg':
                rawBytes.append(registerToByte(parameter))

        codeBytesNewlines.append(len(rawBytes)-1)

print("/*")
print("Generated by Bit OS Machine Langauge Compiler")
print("File:", sys.argv[1])
print("Total Size:", bytesToHumanReadable(len(rawBytes)))
print("Time Compiled:", getCurrentTimeAsString())
print()

print("Data Memory Locations")
for var in mlocLocations:
    print(' ', var + ':', mlocLocations[var])
for i, x in enumerate(rawBytes):
    if type(x) == str:
        mloc = numToArray(8, mlocLocations[x])
        for y in range(0, 8):
            rawBytes[y + i] = mloc[y]
print("*/")
print("#include <stdint.h>")
print("#define EXE_SIZE", len(rawBytes))
print("uint8_t exeContent[] = {")
print('  ',end = '')
for index, i in enumerate(rawBytes):
    print(i, end = ', ')
    if index in codeBytesNewlines:
        print('\n  ', end = '')
print("\n};", end = '')