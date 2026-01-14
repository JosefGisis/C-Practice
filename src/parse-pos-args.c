#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse-args.h"

int pos_arg_index = 1;

int get_pos_arg(const int argc, char *argv[], char *value) {
    memset(value, '\0', MAX_ARG_VAL_LENGTH);

    for (; pos_arg_index < argc && argv[pos_arg_index][0] == '-'; pos_arg_index++) {
    }
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

// Turns the arg pattern string into a more easy to read integer array.
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

int get_all_pos_args(const int argc, char *argv[], const char *pattern,
                     char value[MAX_ARGS_LENGTH][MAX_ARG_VAL_LENGTH]) {
    // Return early for empty pattern
    if (strlen(pattern) == 0) {
        return SUCCESS;
    }

    int numerical_pattern[3] = {0, 0, 0};
    const int result = get_numerical_pattern(pattern, numerical_pattern);
    if (result == ERROR) return result;

    const int total = (numerical_pattern[0] + numerical_pattern[2]);

    if (total > MAX_ARGS_LENGTH) {
        fprintf(stderr, "Provided pattern would exceed maximum argument length\n");
        return ERROR;
    }

    if (total > argc - 1) {
        fprintf(stderr, "Insufficient positional arguments provided %i for pattern %s\n", argc - 1, pattern);
        return ERROR;
    }

    // The user has provided an empty pattern
    if (total == 0 && numerical_pattern[1] == 0) return SUCCESS;

    // These two indices are used to make sure the leading and trailing arguments do not overlap (double-dip)
    int pre_catch_all_index = 1;
    int post_catch_all_index = argc - 1;

    // Counts are used to add items to the provided string array
    int pre_catch_all_count = 0;
    int post_catch_all_count = 0;
    int catch_all_count = 0;

    // Where the pattern specifies some pre catch-all args
    if (numerical_pattern[0] > 0) {
        for (; pre_catch_all_count < numerical_pattern[0]; pre_catch_all_index++) {
            if (pre_catch_all_index >= argc) {
                fprintf(stderr, "Error: Insufficient positional arguments provided for pattern %s", pattern);
                return ERROR;
            }
            if (argv[pre_catch_all_index][0] == '=') {
                fprintf(stderr, "Error: Positional argument started with '='\n");
                return ERROR;
            }
            if (argv[pre_catch_all_index][0] != '-') {
                strcpy(value[pre_catch_all_count], argv[pre_catch_all_index]);
                pre_catch_all_count++;
            }
        }
    }

    if (pre_catch_all_count != numerical_pattern[0]) {
        fprintf(stderr, "Insufficient arguments provided for pattern %s\n", pattern);
        return ERROR;
    }

    // We need to get post catch all args before going through catch all args, so we need to store them temporarily.
    char post_catch_all_temp[MAX_ARGS_LENGTH][MAX_ARG_VAL_LENGTH] = {0};
    // Where we have some post catch-all args in our pattern
    if (numerical_pattern[2] > 0) {
        for (; post_catch_all_index > 0 && post_catch_all_count < numerical_pattern[2]; post_catch_all_index--) {
            if (post_catch_all_index < pre_catch_all_index) {
                fprintf(stderr, "Insufficient arguments provided for pattern %s\n", pattern);
                return ERROR;
            }

            if (argv[post_catch_all_index][0] == '=') {
                fprintf(stderr, "Error: Positional argument started with '='\n");
                return ERROR;
            }

            if (argv[post_catch_all_index][0] != '-') {
                strcpy(post_catch_all_temp[post_catch_all_count], argv[post_catch_all_index]);
                post_catch_all_count++;
            }
        }
    }

    if (post_catch_all_count != numerical_pattern[2]) {
        fprintf(stderr, "Insufficient arguments provided for pattern %s\n", pattern);
        return ERROR;
    }

    // Where we have a catch all somewhere in the pattern
    if (numerical_pattern[1] > 0) {
        // Iterate over the end of where we parsed pre args and the beginning of where we ended post.
        for (int i = pre_catch_all_index; i < (post_catch_all_index + 1); i++) {
            if (argv[i][0] == '=') {
                fprintf(stderr, "Error: Positional argument started with '='\n");
                return ERROR;
            }

            if (argv[i][0] != '-') {
                strcpy(value[catch_all_count + pre_catch_all_count], argv[i]);
                catch_all_count++;
                if ((catch_all_count + post_catch_all_count + pre_catch_all_count) > MAX_ARGS_LENGTH) {
                    fprintf(stderr, "Argument count exceeded max arg length");
                    return ERROR;
                }
            }
        }
    }

    // We need to add the post catch all args back onto the end of the array
    if (post_catch_all_count > 0) {
        for (int i = pre_catch_all_count + catch_all_count, j = post_catch_all_count - 1; j >= 0; i++, j--) {
            strcpy(value[i], post_catch_all_temp[j]);
        }
    }

    return SUCCESS;
};
