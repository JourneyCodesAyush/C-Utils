#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dispatcher.h"
#include "head.h"
#include "tail.h"
#include "command_pwd.h"
#include "wc.h"
#include "cp.h"
#include "whoami.h"
#include "help.h"
#include "version.h"

int head_cmd(int argc, const char **argv)
{
    if (argc == 2)
    {
        command_head(argv[1], 10);
    }
    else if (argc == 3 && argv[1][0] == '-') // head -n file or head -5 file
    {
        char *endptr;
        long number = strtol(argv[1], &endptr, 10);
        if (*endptr != '\0')
        {
            fprintf(stderr, "Invalid line count: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
        if (number < 0)
            number *= -1;
        command_head(argv[2], number);
    }
    else
    {
        command_help();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int tail_cmd(int argc, const char **argv)
{
    if (argc == 2)
    {
        command_tail(argv[1], 10);
    }
    else if (argc == 3 && argv[1][0] == '-') // tail -n file or tail -5 file
    {
        char *endptr;
        long number = strtol(argv[1], &endptr, 10);
        if (*endptr != '\0')
        {
            fprintf(stderr, "Invalid line count: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
        if (number < 0)
            number *= -1;
        command_tail(argv[2], number);
    }
    else
    {
        command_help();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int pwd_cmd(int argc, const char **argv)
{
    command_pwd();
    return EXIT_SUCCESS;
}

int wc_cmd(int argc, const char **argv)
{
    WCOptions opts = {true, true, true};
    int file_index = 1;

    if (argc >= 2 && argv[1][0] == '-')
    {
        opts.print_chars = false;
        opts.print_lines = false;
        opts.print_words = false;
        for (const char *p = argv[1] + 1; *p; p++)
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
                return EXIT_FAILURE;
            }
        }
        file_index = 2;
    }

    if (argc <= file_index)
    {
        fprintf(stderr, "Missing filename for wc\n");
        return EXIT_FAILURE;
    }

    command_wc(argv[file_index], &opts);
    return EXIT_SUCCESS;
}

int cp_cmd(int argc, const char **argv)
{
    bool interactive = false;
    const char *source = NULL;
    const char *destination = NULL;

    for (int i = 1; i < argc; i++)
    {
        const char *arg = argv[i];

        // long flags: --interactive
        if (arg[0] == '-' && arg[1] == '-')
        {
            if (strcmp(arg, "--interactive") == 0)
            {
                interactive = true;
            }
            else
            {
                fprintf(stderr, "Unknown option: %s\n", arg);
                return EXIT_FAILURE;
            }
        }
        // short flags: -i
        else if (arg[0] == '-' && arg[1] != '\0')
        {
            for (const char *p = arg + 1; *p; p++)
            {
                if (*p == 'i')
                {
                    interactive = true;
                }
                else
                {
                    fprintf(stderr, "Unknown option: -%c\n", *p);
                    return EXIT_FAILURE;
                }
            }
        }
        // positional args
        else
        {
            if (!source)
            {
                source = arg;
            }
            else if (!destination)
            {
                destination = arg;
            }
            else
            {
                fprintf(stderr, "cutils: too many arguments for cp\n");
                return EXIT_FAILURE;
            }
        }
    }

    // validation
    if (!source || !destination)
    {
        command_help();
        return EXIT_FAILURE;
    }

    command_cp(source, destination, interactive);
    return EXIT_SUCCESS;
}

int whoami_cmd(int argc, const char **argv)
{
    if (argc > 1)
    {
        command_help();
        return EXIT_FAILURE;
    }
    command_whoami();
    return EXIT_SUCCESS;
}

int help_cmd(int argc, const char **argv)
{
    command_help();
    return EXIT_SUCCESS;
}

Command commands[] = {
    {"head", head_cmd, "Print first n lines of a file"},
    {"tail", tail_cmd, "Print last n lines of a file"},
    {"pwd", pwd_cmd, "Print current working directory"},
    {"wc", wc_cmd, "Count lines, words, characters"},
    {"cp", cp_cmd, "Copy file from source to destination"},
    {"whoami", whoami_cmd, "Print current user name"},
    {"help", help_cmd, "Show help message"},
    {NULL, NULL, NULL} // sentinel
};

void command_dispatcher(int argc, const char *argv[])
{
    if (argc < 2)
    {
        command_help();
        exit(EXIT_FAILURE);
    }

    const char *cmd_name = argv[1];

    if (strcmp(cmd_name, "-h") == 0 || strcmp(cmd_name, "--help") == 0)
    {
        command_help();
        exit(EXIT_SUCCESS);
    }

    if (strcmp(cmd_name, "-v") == 0 || strcmp(cmd_name, "--version") == 0)
    {
        if (argc > 2)
        {
            command_help();
            exit(EXIT_FAILURE);
        }
        fprintf(stdout, "%s\n", __version__);
        exit(EXIT_SUCCESS);
    }

    for (Command *c = commands; c->name; c++)
    {
        if (strcmp(cmd_name, c->name) == 0)
        {

            int result = c->func(argc - 1, argv + 1);
            exit(result);
        }
    }

    fprintf(stderr, "Unknown command: %s\n", cmd_name);
    command_help();
    exit(EXIT_FAILURE);
}
