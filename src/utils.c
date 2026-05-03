#include <stdio.h>
#include <stdbool.h>

#include "utils.h"

bool confirm_overwrite(const char *message)
{
    printf("%s", message);
    fflush(stdout);
    int c = getchar();

    if (c == EOF)
        return false;

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    return (c == 'y' || c == 'Y');
}
