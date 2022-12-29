// #pragma once
// #include <stddef.h>
// #include <stdint.h>

// class ConservedBoolean
// {
//     public:
//         size_t Size;
//         uint8_t* Buffer;
//         bool Get(uint64_t index){
//             uint64_t byteIndex = index / 8;
//             uint8_t bitIndex = index % 8;
//             if ((Buffer[byteIndex] & (1 << bitIndex)) != 0){
//                 return true;
//             }
//             return false;
//         };
//         void Set(uint64_t index, bool value){
//             uint64_t byteIndex = index / 8;
//             uint8_t bitIndex = index % 8;
//             uint8_t bitIndexer = 1 << bitIndex;
//             Buffer[byteIndex] &= ~bitIndexer;
//             if (value){
//                 Buffer[byteIndex] |= bitIndexer;
//             }
//         }
// };
