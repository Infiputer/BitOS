#pragma once
static char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

static bool isAlpha(char c){
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
        return true;
    }
    return false;
}

static char toUpper(char c){
    return c+('A'-'a');
}

// int strcmp(const char *s1, const char *s2) {
//   const unsigned char *us1 = (const unsigned char *) s1;
//   const unsigned char *us2 = (const unsigned char *) s2;
//   while (*us1 == *us2 && *us1 != '\0') {
//     us1++;
//     us2++;
//   }
//   return (*us1 > *us2) - (*us1 < *us2);
// }

static size_t strlen(const char* str)
{
    size_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
}

