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

    char * patter_1 = "---*--";
    char * patter_2 = "---*";
    char * patter_3 = "--*-";
    char * patter_4 = "-h-";

    get_all_pos_args(argc, argv, patter_1, argv);
    get_all_pos_args(argc, argv, patter_2, argv);
    get_all_pos_args(argc, argv, patter_3, argv);
    get_all_pos_args(argc, argv, patter_4, argv);

    free(key);
    free(value);
    reset_opt_arg_parser();
    reset_pos_arg_parser();

    return SUCCESS;
};

