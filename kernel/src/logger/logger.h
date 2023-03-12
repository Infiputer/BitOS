#pragma once
#include <stdint.h>

#define LOG_LIGHT_RED      65
#define LOG_LIGHT_ORANGE   66
#define LOG_LIGHT_YELLOW   67
#define LOG_LIGHT_GREEN    68
#define LOG_LIGHT_BLUE     69
#define LOG_LIGHT_PURPLE   70
#define LOG_LIGHT_BLACK    71
#define LOG_LIGHT_BROWN    72
#define LOG_RED            73
#define LOG_ORANGE         74
#define LOG_YELLOW         75
#define LOG_GREEN          76
#define LOG_BLUE           77
#define LOG_PURPLE         78
#define LOG_WHITE          79
#define LOG_BLACK          80
#define LOG_BROWN          81
#define LOG_DARK_RED       82
#define LOG_DARK_ORANGE    83
#define LOG_DARK_YELLOW    84
#define LOG_DARK_GREEN     85
#define LOG_DARK_BLUE      86
#define LOG_DARK_PURPLE    87
#define LOG_DARK_BROWN     88

void InitLog();

void log(const char * msg, uint8_t fgcolor = LOG_WHITE, uint8_t bgcolor = LOG_BLACK, char end = '\n');

void showLog();