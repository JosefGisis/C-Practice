#include "parse-args.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <_stdio.h>
#include <_string.h>
#define MAX_VALUE_LENGTH 1000

// We start with 1 as argv[0] is the command name (e.g. parse-args)
int get_opt_arg_index = 1;
// Preserves the position of the bundled flags being traversed
int get_opt_arg_bookmark = 0;

// Fetches the next optional argument from provided argv.
// Return 1 for a successful arg return, 0 for end of optional arguments, and -1 for an error.
int get_opt_arg(const int argc, char *argv[], char *key, char *value) {
    // Clear out key and value
    memset(key, '\0', MAX_ARG_KEY_LENGTH);
    memset(value, '\0', MAX_ARG_VAL_LENGTH);
    // Resume traversing grouped flags
    // if (get_opt_arg_bookmark > 0) {
    //     const char current_char = argv[get_opt_arg_index][get_opt_arg_bookmark++];
    //     if (current_char == '\0' || current_char == '\n' || current_char == '=') {
    //         get_opt_arg_bookmark = 0;
    //         get_opt_arg_index++;
    //     } else {
    //         *key = current_char;
    //         value[0] = '\0';
    //         return SUCCESS;
    //     }
    // }

    // Skip all non-optional arguments up until the end of argv
    for (; get_opt_arg_index < argc && argv[get_opt_arg_index][0] != '-'; get_opt_arg_index++) {}
    if (get_opt_arg_index >= argc) return EOA;


    // Move through the arg until the last dash
    for (; argv[get_opt_arg_index][get_opt_arg_bookmark] == '-' && get_opt_arg_bookmark < 2; get_opt_arg_bookmark++) {
    }

    // Users should not provide empty optional args
    if (argv[get_opt_arg_index][get_opt_arg_bookmark] == '\0') {
        fprintf(stderr, "error: invalid option '%s'\n", argv[get_opt_arg_index]);
        exit(1);
    }

    const bool isFlag = get_opt_arg_bookmark == 1;
    const char *arg_start = argv[get_opt_arg_index] + get_opt_arg_bookmark;

    const char *value_segment = strchr(arg_start, '=');
    const size_t key_len = strcspn(arg_start, "=");

    if (isFlag && key_len > 1 && value_segment != NULL) {
        fprintf(stderr, "error: invalid option '%s'. Cannot provide a value for grouped flags\n", arg_start);
        exit(1);
    }

    if (!isFlag || key_len == 1) {
        // Calculate how much we can safely copy
        const size_t copy_len = key_len >= MAX_ARG_KEY_LENGTH ? MAX_ARG_KEY_LENGTH - 1 : key_len;

        strncpy(key, arg_start, copy_len);
        key[copy_len] = '\0';  // Null terminate at the position we copied to

        if (value_segment != NULL) {
            strncpy(value, value_segment + 1, MAX_VALUE_LENGTH - 1);
            value[MAX_VALUE_LENGTH - 1] = '\0';
        }
        get_opt_arg_index++;
        get_opt_arg_bookmark = 0;
        return SUCCESS;
    }

    // if (argv[get_opt_arg_index][get_opt_arg_bookmark] == '\0') {
    //     return ERROR;
    // }
    //
    // if (get_opt_arg_bookmark == 1) {
    //     value[0] = '\0';
    //     const char current_char = argv[get_opt_arg_index][get_opt_arg_bookmark++];
    //
    //     if (current_char == '\0' || current_char == '\n' || current_char == '=') {
    //         get_opt_arg_bookmark = 0;
    //         return ERROR;
    //     }
    //
    //     *key = current_char;
    //     return SUCCESS;
    // }
    //
    //
    // const char *value_segment = strchr(argv[get_opt_arg_index], '=');
    // if (value_segment == NULL) {
    //     value[0] = '\0';
    // } else {
    //     strncpy(value, value_segment + 1, MAX_VALUE_LENGTH);
    // }
    // get_opt_arg_index++;
    // get_opt_arg_bookmark = 0;
    get_opt_arg_index++;
    return ERROR;
};

void reset_opt_arg_parser(void) {
    get_opt_arg_index = 1;
    get_opt_arg_bookmark = 0;
}

