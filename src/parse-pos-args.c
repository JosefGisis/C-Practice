#include <stdio.h>
#include <string.h>
#include "parse-args.h"

int pos_arg_index = 1;

int get_pos_arg(const int argc, char *argv[], char *value) {
    memset(value, '\0', MAX_ARG_VAL_LENGTH);

    for (; pos_arg_index < argc && argv[pos_arg_index][0] == '-'; pos_arg_index++) {}
    if (pos_arg_index >= argc) {
        return EOA;
    }

    if (argv[pos_arg_index][0] == '=') {
        fprintf(
            stderr,
            "Error: Positional argument started with '=' for argument: %s. This may indicate an accidental space in an optional argument\n",
            argv[pos_arg_index]);
        return ERROR;
    }
    strncpy(value, argv[pos_arg_index], MAX_ARG_VAL_LENGTH - 1);
    value[MAX_ARG_VAL_LENGTH - 1] = '\0';
    pos_arg_index++;
    return SUCCESS;
}

void reset_pos_arg_parser(void) {
    pos_arg_index = 0;
}

int get_numerical_pattern(const char *pattern, int value[]) {
    int catch_all_tokens = 0;
    int pre_catch_all_tokens = 0;
    int post_catch_all_tokens = 0;
    for (int i = 0; pattern[i] != '\0'; i++) {
        if (pattern[i] != '-' && pattern[i] != '*' && pattern[i] != '\0') {
            fprintf(stderr, "Invalid char %c found in argument pattern at pos %i\n", pattern[i], i);
            return ERROR;
        }
        if (pattern[i] == '*' && catch_all_tokens > 0) {
            fprintf(
                stderr,
                "More than one catch-all tokens provided in argument pattern. Multiple catch-all tokens creates an ambiguous pattern.\n");
            return ERROR;
        }
        if (pattern[i] == '*') {
            catch_all_tokens++;
        } else if (pattern[i] == '-') {
            if (catch_all_tokens == 0) {
                pre_catch_all_tokens++;
            } else {
                post_catch_all_tokens++;
            }
        }
    }

    value[0] = pre_catch_all_tokens;
    value[1] = catch_all_tokens;
    value[2] = post_catch_all_tokens;
    return SUCCESS;
}


int get_all_pos_args(int argc, char *argv[], const char * pattern, char * value[]) {
    int numerical_pattern[3] = {0, 0, 0};
    const int result = get_numerical_pattern(pattern, numerical_pattern);
    if (result == ERROR) {
        printf("Error in result");
        return result;
    }
    printf("For pattern %s\n", pattern);
    for (int i = 0; i < 3; i++) {
        printf("value at index %i is %i\n", i, numerical_pattern[i]);
    }
    return SUCCESS;
};
