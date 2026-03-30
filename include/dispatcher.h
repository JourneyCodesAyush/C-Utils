#ifndef C_UTILS_DISPATCHER_H
#define C_UTILS_DISPATCHER_H

typedef int (*command_func)(int argc, const char *argv[]);
typedef struct
{
    const char *name;
    command_func func;
    const char *help;
} Command;

// Takes number of command arguments and commands and calls appropriate functions
void command_dispatcher(int argc, const char *argv[]);

#endif // C_UTILS_DISPATCHER_H