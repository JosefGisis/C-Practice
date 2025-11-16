#include <stdio.h>
#include <stdlib.h>
#include "parse-args.h"
#define TRUE 1
#define FALSE 0

int main(const int argc, char **argv) {
    char *key = malloc(1);
    char *value = malloc(1);

    for (int i=1; i < argc; i++) {
        const int result = get_opt_args(argc, argv, key, value);

        if (result == 1) {
            printf("key=%s value=%s\n", key, value);
        } else if (result == 0) {
            printf("Reached end of arguments\n");
        } else if (result == -1) {
            printf("Failed to parse output\n");
        }
    }

    free(key);
    free(value);

    return 0;
}
