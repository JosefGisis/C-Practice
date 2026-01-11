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
    // Clear out key and value to prevent previous key/value from persisting
    memset(key, '\0', MAX_ARG_KEY_LENGTH);
    memset(value, '\0', MAX_ARG_VAL_LENGTH);

    // Resume traversing grouped flags
    if (get_opt_arg_bookmark > 0) {
        get_opt_arg_bookmark++;
        if (get_opt_arg_bookmark > MAX_ARG_KEY_LENGTH) {
            fprintf(stderr, "Compound flag has exceeded max length of %i\n", MAX_ARG_KEY_LENGTH);
            fflush(stdout);
            return ERROR;
        }
         if (argv[get_opt_arg_index][get_opt_arg_bookmark] == '=' || argv[get_opt_arg_index][get_opt_arg_bookmark] == '-') {
            fprintf(stderr, "Invalid character provided in compound flag\n");
             fflush(stdout);
            return ERROR;
        }

        if (argv[get_opt_arg_index][get_opt_arg_bookmark] == '\0') {
            get_opt_arg_bookmark = 0;
            get_opt_arg_index++;
        } else {
            *key = argv[get_opt_arg_index][get_opt_arg_bookmark];
            return SUCCESS;
        }
    }

    // Skip all non-optional arguments up until the end of argv
    for (; get_opt_arg_index < argc && argv[get_opt_arg_index][0] != '-'; get_opt_arg_index++) {
    }
    if (get_opt_arg_index >= argc) {
        return EOA;
    }

    // move through the first one or two dashes
    for (; argv[get_opt_arg_index][get_opt_arg_bookmark] == '-' && get_opt_arg_bookmark < 3; get_opt_arg_bookmark++) {
    }
    if (get_opt_arg_bookmark > 2) {
        fprintf(stderr, "Optional arguments must either start with a double or single dash");
        fflush(stdout);
        return ERROR;
    }

    // Users should not provide empty optional args
    if (argv[get_opt_arg_index][get_opt_arg_bookmark] == '\0') {
        fprintf(stderr, "Error: Empty optional argument provided");
        fflush(stdout);
        return ERROR;
    }

    const bool isFlag = get_opt_arg_bookmark == 1;
    const char *arg_start = argv[get_opt_arg_index] + get_opt_arg_bookmark;
    // Extract the part of the argument after the equal sign
    const char *value_segment = strchr(arg_start, '=');
    // Get the length of the arguments key. This is used to extract the key or catch invalid syntax
    const size_t key_len = strcspn(arg_start, "=");

    if (isFlag && key_len > 1 && value_segment != NULL) {
        fprintf(stderr, "error: invalid option '%s'. Cannot provide a value for grouped flags\n", arg_start);
        fflush(stdout);
        return ERROR;
    }

    // Non flag or single flag args are not iterated over and can return a key and value
    if (!isFlag || key_len == 1) {
        // Calculate how much we can safely copy
        const size_t copy_len = key_len >= MAX_ARG_KEY_LENGTH ? MAX_ARG_KEY_LENGTH - 1 : key_len;

        strncpy(key, arg_start, copy_len);
        key[copy_len] = '\0';

        if (value_segment != NULL) {
            strncpy(value, value_segment + 1, MAX_VALUE_LENGTH - 1);
            value[MAX_VALUE_LENGTH - 1] = '\0';
        }
        get_opt_arg_index++;
        // Do not iterate over arg.
        get_opt_arg_bookmark = 0;
        return SUCCESS;
    }

    // With compound flags we just return the first one. See the start of this function
    // For how we iterate over the rest of the items
    if (key_len > 1) {
        *key = arg_start[0];
        return SUCCESS;
    }

    return ERROR;
}

void reset_opt_arg_parser(void) {
    get_opt_arg_index = 1;
    get_opt_arg_bookmark = 0;
}
