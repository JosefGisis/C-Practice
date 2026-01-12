#include "parse-args.h"
#include <stdio.h>
#include <stdlib.h>

int main(const int argc, char **argv) {
    char *key = malloc(sizeof(char) * MAX_ARG_VAL_LENGTH);
    char *value = malloc(sizeof(char) * MAX_ARG_VAL_LENGTH);

    for (int i = 1, end_of_args = FALSE; i <= MAX_ARGS_LENGTH && !end_of_args; i++) {
        const int result = get_opt_arg(argc, argv, key, value);

        if (result == EOA) {
            end_of_args = TRUE;
            printf("Reached end of optional arguments\n");
        } else if (result == SUCCESS) {
            printf("key=%s value=%s\n", key, value);
        } else if (result == ERROR) {
            exit(EXIT_FAILURE);
        }
    }

    //
    // for (int i=TRUE; i == TRUE ; i++) {
    //     const int result = get_opt_args(argc, argv, key, value);
    //
    //     if (result == 0) {
    //         printf("Reached end of optional arguments\n");
    //     } else if (result == 1) {
    //         printf("key=%s value=%s\n", key, value);
    //     } else if (result == -1) {
    //         printf("Failed to parse output\n");
    //     }
    //
    //     if (i == argc -1 && result != 0) {
    //         printf("Reached end of arguments\n");
    //     }
    // }

    free(key);
    free(value);
    reset_opt_arg_parser();

    return 0;
};

