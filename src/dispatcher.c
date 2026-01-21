#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dispatcher.h"
#include "head.h"
#include "tail.h"
#include "pwd.h"
#include "wc.h"
#include "cp.h"
#include "whoami.h"
#include "help.h"

// Dispatch commands based on argv
void command_dispatcher(int argc, const char *argv[])
{
    // Basic argument check and print help message if no argument provided
    if (argc < 2)
    {
        command_help();
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        command_help();
        exit(EXIT_SUCCESS);
    }

    if (strcmp(argv[1], "head") == 0)
    {
        if (argc == 3)
        {
            command_head(argv[2], 10);
        }
        else if (argc == 4)
        {
            char *endptr;
            long number = strtol(argv[2], &endptr, 10);
            if (*endptr != '\0')
            {
                fprintf(stderr, "Invalid line count: %s\n", argv[2]);
                exit(EXIT_FAILURE);
            }
            number *= -1;
            command_head(argv[3], number);
        }
    }
    else if (strcmp(argv[1], "tail") == 0)
    {
        if (argc == 3)
        {
            command_tail(argv[2], 10);
        }
        else if (argc == 4)
        {
            char *endptr;
            long number = strtol(argv[2], &endptr, 10);
            if (*endptr != '\0')
            {
                fprintf(stderr, "Invalid line count: %s\n", argv[2]);
                exit(EXIT_FAILURE);
            }
            number *= -1;
            command_tail(argv[3], number);
        }
    }
    else if (strcmp(argv[1], "pwd") == 0)
    {
        command_pwd();
    }
    else if (strcmp(argv[1], "wc") == 0)
    {
        WCOptions opts = {true, true, true};

        int file_index = 2;
        /*
                if (argc == 3)
                {
                    command_wc(argv[2], opts);
                }
                else if (argc == 4)
                {
                    command_wc(argv[3], opts);
                }
        */
        if (argc >= 3 && argv[2][0] == '-')
        {
            opts.print_chars = false;
            opts.print_lines = false;
            opts.print_words = false;
            for (const char *p = argv[2] + 1; *p; p++)
            {
                if (*p == 'l')
                    opts.print_lines = true;
                else if (*p == 'c')
                    opts.print_chars = true;
                else if (*p == 'w')
                    opts.print_words = true;
                else
                {
                    fprintf(stderr, "Unknown option: -%c\n", *p);
                    exit(EXIT_FAILURE);
                }
            }
            file_index = 3;
        }
        if (argc <= file_index)
        {
            fprintf(stderr, "Missing filename for wc\n");
        }
        command_wc(argv[file_index], &opts);
    }
    else if (strcmp(argv[1], "cp") == 0)
    {
        if (argc < 4)
        {
            command_help();
            exit(EXIT_FAILURE);
        }
        command_cp(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "whoami") == 0)
    {
        if (argc > 2)
        {
            command_help();
            exit(EXIT_FAILURE);
        }
        command_whoami();
    }
    else
    {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        command_help();
        exit(EXIT_FAILURE);
    }
}
