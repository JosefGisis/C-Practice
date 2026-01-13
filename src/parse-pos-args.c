#include <stdio.h>
#include <string.h>
#include "parse-args.h"

int POS_ARG_INDEX = 1;
int get_pos_arg(const int argc, char *argv[], char *value) {
    memset(value, '\0', MAX_ARG_VAL_LENGTH);

    for (; POS_ARG_INDEX < argc && argv[POS_ARG_INDEX][0] == '-'; POS_ARG_INDEX++){}
    if (POS_ARG_INDEX >= argc) {
        return EOA;
    }

    if (argv[POS_ARG_INDEX][0] == '=') {
        fprintf(stderr, "Error: Positional argument started with '=' for argument: %s. This may indicate an accidental space in an optional argument\n", argv[POS_ARG_INDEX]);
        fflush(stderr);
        return ERROR;
    }
    strncpy(value, argv[POS_ARG_INDEX], MAX_ARG_VAL_LENGTH - 1);
    value[MAX_ARG_VAL_LENGTH - 1] = '\0';
    POS_ARG_INDEX++;
    return SUCCESS;
}

void reset_pos_arg_parser(void) {
    POS_ARG_INDEX = 0;
}

int get_all_pos_args();