#include "parse-args.h"
#include <ctype.h>
#include <_string.h>
#include <stdio.h>

#define EOA 0
#define ERROR -1
#define SUCCESS 1
#define MAX_VALUE_LENGTH 1000

int get_opt_arg_index = 1;

int get_opt_args(const int argc, char * argv[], char * key, char * value) {
    if (argc == 1 || get_opt_arg_index >= argc) {
        return EOA;
    }

    // Skip all non-optional arguments up until the end of argv
    for (; get_opt_arg_index < argc && argv[get_opt_arg_index][0] != '-'; get_opt_arg_index++)
        ;

    // If we have traversed the whole list.
    if (get_opt_arg_index >= argc) return EOA;

    // Move through the arg until the last -
    int arg_pos = 0;
    for (; argv[get_opt_arg_index][arg_pos] == '-'; arg_pos++)
        ;

    // The user could have passed just ---
    if (argv[get_opt_arg_index][arg_pos] == '\0') {
        return ERROR;  // Invalid option format
    }

    *key = argv[get_opt_arg_index][arg_pos];

    const char * value_segment = strchr(argv[get_opt_arg_index], '=');
    if (value_segment == NULL) {
        value[0] = '\0';
    } else {
        strncpy(value, value_segment + 1, MAX_VALUE_LENGTH);
    }

    get_opt_arg_index++;
    return SUCCESS;
}

int get_pos_args(int argc, char *argv[], char * pattern, char ** results) {
    return SUCCESS;
}
