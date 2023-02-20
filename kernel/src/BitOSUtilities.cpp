#include <stddef.h>
/** 
 * Converts an integer to a string representation in a specified base
 * 
 * @param value Integer to be converted
 * @param result Buffer to store the result string
 * @param base Base to represent the number in (2 <= base <= 36)
 * 
 * @return Pointer to the result string
 */
char *itoa(int value, char *result, int base) 
{
    // check that the base if valid
    if (base < 2 || base > 36)
    {
        *result = '\0';
        return result;
    }

    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do
    {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
    } while (value);

    // Apply negative sign
    if (tmp_value < 0)
        *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

/**

* Determines whether a character is an alphabet or not
*
* @param c The character to be checked
*
* @return True if the character is an alphabet (either uppercase or lowercase), false otherwise
*/
bool isAlpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        return true;
    }
    return false;
}

/**

* Converts a lowercase character to its uppercase equivalent 
*
* @param c The lowercase character to be converted
*
* @return The uppercase equivalent of the given character
*/
char toUpper(char c)
{
    return c + ('A' - 'a');
}

/**

* @brief This function compares two strings
* @param[in] s1 The first string to compare
* @param[in] s2 The second string to compare
* @return Returns 0 if s1 and s2 are equal, less than 0 if s1 is lexicographically smaller than s2, and greater than 0 if s1 is lexicographically larger than s2.
*/
int strcmp(const char *s1, const char *s2)
{
    const unsigned char *us1 = (const unsigned char *)s1;
    const unsigned char *us2 = (const unsigned char *)s2;
    while (*us1 == *us2 && *us1 != '\0')
    {
        us1++;
        us2++;
    }
    return (*us1 > *us2) - (*us1 < *us2);
}

/**

* Returns the length of a string
* @param str The input string
* @return size_t The length of the string
*/
size_t strlen(const char *str)
{
    size_t ret = 0;
    while (str[ret] != 0)
        ret++;
    return ret;
}
