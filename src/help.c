#include <stdio.h>

#include "help.h"

void command_help()
{
    // fprintf(stdout, "C-utils: mini Unix utilities implemented in C\n\n");
    fprintf(stdout, "\nC-utils: Minimal Unix utilities in C\n\nAuthor: JourneyCodesAyush\nRepo: https://github.com/journeycodesayush/c-utils\nFor educational purposes only.\n\n");
    fprintf(stdout, "Usage:\n");
    fprintf(stdout, "  cutils <command> [options]\n\n");
    fprintf(stdout, "Commands implemented:\n");
    fprintf(stdout, "  head <filename>           Print first 10 lines of a file\n");
    fprintf(stdout, "  head -n <file>            Print first n lines\n");
    fprintf(stdout, "  tail <filename>           Print last 10 lines of a file\n");
    fprintf(stdout, "  tail -n <file>            Print last n lines\n");
    fprintf(stdout, "  pwd                       Print current working directory\n");
    fprintf(stdout, "  cp <source> <destination> Copies file at source to destination\n");
    fprintf(stdout, "  -h, --help                Show this help message\n");
}
