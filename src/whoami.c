#include <stdio.h>
#include <stdlib.h>

#include "whoami.h"

// Include appropriate header file for Windows and Linux environments
#if defined(_WIN32) || defined(_WIN64)
#define USER "USERNAME"
#include <windows.h>
#include <Lmcons.h>
#else
#define USER "USER"
#include <unistd.h>
#include <pwd.h>
#endif

// Compile functions suited for OS
#if defined(_WIN32) || defined(_WIN64)
static void fallback_for_windows()
{
    // Code taken from stack overflow
    TCHAR windows_user_name[UNLEN + 1];
    DWORD size = UNLEN + 1;

    if (GetUserName(windows_user_name, &size))
    {
        fprintf(stdout, "%s\n", windows_user_name);
        exit(EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "Couldn't get user name\n");
    }
}

// For unix machines incase  getenv() fails
#else
static void fallback_for_unix()
{
    uid_t uid = getuid();

    struct passwd *pw = getpwuid(uid);
    if (pw == NULL)
    {
        fprintf(stderr, "Couldn't get user name\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "%s\n", pw->pw_name);
    exit(EXIT_SUCCESS);
}
#endif

void command_whoami()
{
    char *name = getenv(USER);
    if (name != NULL)
    {
        fprintf(stdout, "%s\n", name);
    }
    else
    {
#if defined(_WIN32) || defined(_WIN64)
        fallback_for_windows();
#else
        fallback_for_unix();
#endif
    }
}
