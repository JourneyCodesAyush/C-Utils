#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "wc.h"

void command_wc(const char *filename, WCOptions *options)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int lines = 0, words = 0, chars = 0;
    int c;

    bool inside_word = false;

    while ((c = fgetc(fp)) != EOF)
    {
        chars++;

        if (isspace(c))
        {
            inside_word = false;
            if (c == '\n')
                lines++;
        }
        else if (!inside_word)
        {
            words++;
            inside_word = true;
        }
    }

    if (options->print_chars && options->print_lines && options->print_words)
        fprintf(stdout, "%d\t%d\t%d\t", lines, words, chars);
    else
    {

        if (options->print_chars)
            fprintf(stdout, "%d\t", chars);
        if (options->print_lines)
            fprintf(stdout, "%d\t", lines);
        if (options->print_words)
            fprintf(stdout, "%d\t", words);
    }

    fprintf(stdout, "%s\n", filename);
    fclose(fp);
}