#ifndef C_UTILS_WC_H
#define C_UTILS_WC_H

#include <stdbool.h>

typedef struct
{
    bool print_lines;
    bool print_words;
    bool print_chars;
} WCOptions;

void command_wc(const char *filename, WCOptions *options);

#endif // C_UTILS_WC_H