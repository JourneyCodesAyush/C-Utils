#include <stdio.h>
#include <stdlib.h>

#include "tail.h"
#include "common.h"

// Get total number of lines in a file
static int get_lines_in_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "Couldn't open file: %s\n", filename);
        return -1;
    }

    int lines_count = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
            lines_count++;
    }

    fclose(fp);
    return lines_count;
}

// Print the last 'number_of_lines' lines of a file
void command_tail(const char *filename, int number_of_lines)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "Couldn't open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Lines exceeding characters than MAX_CHARS_IN_LINE are automatically truncated
    char line[MAX_CHARS_IN_LINE];

    int total_lines = get_lines_in_file(filename);
    if (total_lines < 0)
    {
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    int lines_to_skip = total_lines - number_of_lines;
    if (lines_to_skip < 0)
        lines_to_skip = 0;

    // Skip lines to reach the last 'number_of_lines'
    for (size_t i = 0; i < lines_to_skip; i++)
    {
        if (!fgets(line, MAX_CHARS_IN_LINE, fp))
            break;
    }

    // Print the remaining lines
    while (fgets(line, MAX_CHARS_IN_LINE, fp))
    {
        fprintf(stdout, "%s", line);
    }

    fclose(fp);
}
