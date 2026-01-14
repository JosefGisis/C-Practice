#include "parse-args.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(const int argc, char **argv) {
    setbuf(stdout, NULL);
    char *key = malloc(sizeof(char) * MAX_ARG_VAL_LENGTH);
    char *value = malloc(sizeof(char) * MAX_ARG_VAL_LENGTH);

    for (int i = 1, end_of_args = FALSE; i <= MAX_ARGS_LENGTH && !end_of_args; i++) {
        const int result = get_opt_arg(argc, argv, key, value);

        if (result == EOA) {
            end_of_args = TRUE;
            printf("Reached end of optional arguments\n");
            fflush(stdout);
        } else if (result == SUCCESS) {
            printf("key=%s value=%s\n", key, value);
            fflush(stdout);
        } else if (result == ERROR) {
            exit(EXIT_FAILURE);
        }
    }

    memset(key, 0, sizeof(char) * MAX_ARG_VAL_LENGTH);
    for (int i = 1, end_of_args = FALSE; i <= MAX_ARGS_LENGTH && !end_of_args; i++) {
        const int result = get_pos_arg(argc, argv, value);

        if (result == EOA) {
            end_of_args = TRUE;
            printf("Reached end of positional arguments\n");
            fflush(stdout);
        } else if (result == SUCCESS) {
            printf("arg=%s\n", value);
            fflush(stdout);
        } else if (result == ERROR) {
            exit(EXIT_FAILURE);
        }
    }

    const char *pattern = "----*";

    // Allocate MAX_ARGS_LENGTH strings of MAX_ARG_VAL_LENGTH. Initialized to \0
    char all_args[MAX_ARGS_LENGTH][MAX_ARG_VAL_LENGTH] = {0};

    get_all_pos_args(argc, argv, pattern, all_args);

    for (int i = 0, end_of_args = FALSE; end_of_args == FALSE && i < MAX_ARGS_LENGTH; i++) {
        if (all_args[i][0] != '\0') {
            printf("Argument number %i is: %s\n", i + 1, all_args[i]);
        } else {
            end_of_args = TRUE;
        }
    }

    free(key);
    free(value);
    reset_opt_arg_parser();
    reset_pos_arg_parser();

    return SUCCESS;
};
