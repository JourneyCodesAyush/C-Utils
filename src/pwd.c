// Include appropriate header file for Windows and Linux environments
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#define get_current_dir _getcwd
#else
#include <unistd.h>
#define get_current_dir getcwd
#endif

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "pwd.h"

void command_pwd()
{
    char cwd[MAX_CHARS_IN_LINE];
    if (get_current_dir(cwd, MAX_CHARS_IN_LINE) != NULL)
    {
        fprintf(stdout, "%s\n", cwd);
    }
    else
    {
        // perror("pwd failed!\n");
        fprintf(stderr, "pwd failed to fetch present working directory\n");
        exit(EXIT_FAILURE);
    }
}