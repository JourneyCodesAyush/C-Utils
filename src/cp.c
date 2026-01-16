#include <stdio.h>
#include <stdlib.h>

#include "cp.h"

void command_cp(const char *source, const char *destination)
{
    FILE *f1 = fopen(source, "r");
    FILE *f2 = fopen(destination, "w");

    if (f1 == NULL)
    {
        fprintf(stderr, "Couldn't open file: %s\n", source);
        if (f2 != NULL)
            fclose(f2);

        exit(EXIT_FAILURE);
    }

    if (f2 == NULL)
    {
        fprintf(stderr, "Couldn't open file: %s\n", destination);
        if (f1 != NULL)
            fclose(f1);

        exit(EXIT_FAILURE);
    }

    int ch;
    while (1)
    {
        ch = fgetc(f1);
        if (ch == EOF)
            break;
        else
        {
            int res;
            res = fputc((char)ch, f2);
            if (res == EOF)
            {
                fprintf(stderr, "Couldn't copy file %s to %s\n", source, destination);
                fclose(f1);
                fclose(f2);
                exit(EXIT_FAILURE);
            }
        }
    }

    if (ferror(f1))
    {
        fprintf(stderr, "Error reading file %s\n", source);
        fclose(f1);
        fclose(f2);
        exit(EXIT_FAILURE);
    }

    fclose(f1);
    fclose(f2);
}