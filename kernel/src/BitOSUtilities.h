#pragma once
#include <stddef.h>
#include <stdint.h>
#include "memory/memory.h"
/**
 * Converts an integer to a string representation in a specified base
 *
 * @param value Integer to be converted
 * @param result Buffer to store the result string
 * @param base Base to represent the number in (2 <= base <= 36)
 *
 * @return Pointer to the result string
 */
char *itoa(int value, char *result, int base);
/**

* Determines whether a character is an alphabet or not
*
* @param c The character to be checked
*
* @return True if the character is an alphabet (either uppercase or lowercase), false otherwise
*/
bool isAlpha(char c);
/**

* Converts a lowercase character to its uppercase equivalent
*
* @param c The lowercase character to be converted
*
* @return The uppercase equivalent of the given character
*/
char toUpper(char c);
/**
 * This function compares two strings
 * @param[in] s1 The first string to compare
 * @param[in] s2 The second string to compare
 * @return Returns 0 if s1 and s2 are equal, less than 0 if s1 is lexicographically smaller than s2, and greater than 0 if s1 is lexicographically larger than s2.
 */
int strcmp(const char *s1, const char *s2);
/**
 * Returns the length of a string
 * @param str The input string
 * @return size_t The length of the string
 */
size_t strlen(const char *str);

/**
 * Sets or clears a bit in an integer value based on the given bit index and value.
 *
 * @param num A pointer to the integer value to modify.
 * @param bitIndex The index of the bit to set or clear (0 is the least significant bit).
 * @param bitValue The value to set or clear the bit to (0 clears the bit, non-zero sets the bit).
 */
uint8_t setBit(uint8_t num, int bitIndex, bool bitValue);

/**
 * Sets or clears a bit in an integer value based on the given bit index and value.
 *
 * @param dest Destination
 * @param src Source
 */
void strcpy(char* dest, const char* src);

/**
 * Checks page by reading and writing data
 * @param p a pointer of the page
*/
bool checkPage(void* p);