#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "head.h"

// Print the first 'number_of_lines' lines of a file
void command_head(const char *filename, int number_of_lines)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "Couldn't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_CHARS_IN_LINE];

    for (int i = 0; i < number_of_lines; i++)
    {
        if (!fgets(line, MAX_CHARS_IN_LINE, fp))
            break;
        fprintf(stdout, "%s", line);
    }

    fclose(fp);
}
