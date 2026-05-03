#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

#include "cp.h"

static void close_files(FILE *f1, FILE *f2)
{
    if (f1)
        fclose(f1);
    if (f2)
        fclose(f2);
}

static bool confirm_overwrite_path(const char *path)
{
    char msg[512];
    snprintf(msg, sizeof(msg), "cutils: overwrite '%s'? [y/n]:", path);

    return confirm_overwrite(msg);
}

static bool file_exists(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (f)
    {
        fclose(f);
        return true;
    }
    return false;
}

static void copy(const char *source, const char *destination)
{
    FILE *f1 = fopen(source, "rb");

    if (f1 == NULL)
    {
        fprintf(stderr, "Couldn't open file: %s\n", source);
        exit(EXIT_FAILURE);
    }

    FILE *f2 = fopen(destination, "wb");

    if (f2 == NULL)
    {
        fprintf(stderr, "Couldn't open file: %s\n", destination);
        if (f1 != NULL)
            fclose(f1);

        exit(EXIT_FAILURE);
    }

    /* Use block I/O for efficiency while remaining portable */
    char buffer[BUFSIZ];

    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), f1)) > 0)
    {
        size_t bytes_written = 0;
        while (bytes_written < bytes_read)
        {
            size_t n = fwrite(buffer + bytes_written, 1, bytes_read - bytes_written, f2);
            if (n == 0)
            {
                fprintf(stderr, "Couldn't copy %s to %s\n", source, destination);
                close_files(f1, f2);
                exit(EXIT_FAILURE);
            }
            bytes_written += n;
        }
    }

    if (ferror(f1))
    {
        fprintf(stderr, "Error reading file %s\n", source);
        close_files(f1, f2);
        exit(EXIT_FAILURE);
    }
    if (ferror(f2))
    {
        fprintf(stderr, "Error reading file %s\n", destination);
        close_files(f1, f2);
        exit(EXIT_FAILURE);
    }

    fclose(f1);
    fclose(f2);
}

void command_cp(const char *source, const char *destination, const bool interactive)
{
    if (strcmp(source, destination) == 0)
    {
        fprintf(stderr, "cutils: '%s' and '%s' are the same file\n", source, destination);
        exit(EXIT_FAILURE);
    }

    if (interactive && file_exists(destination))
    {
        if (!confirm_overwrite_path(destination))
        {
            return;
        }
    }
    copy(source, destination);
}
