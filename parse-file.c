#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define SOURCE "source"
#define USAGE "Usage: parse-file [-options] <file>\n" \

char * get_source(int argc, char *argv[]) {
    int i, found = FALSE;

    if (argc < 2) {
        printf("Insufficient arguments provided. %s\n", USAGE);
        return 0;
    }

    for (i = 1; i < argc && !found; i++) {
        if (strcmp(argv[i], SOURCE) == 0) {
            found = TRUE;
        }
    }

    if (!found) {
        printf("No source specified. %s\n", USAGE);
        return 0;
    }

    char * source_value = argv[i];

    return source_value;
}

int main(const int argc, char **argv) {
    char *source = get_source(argc, argv);

    if (source == NULL) {
        return 1;
    }

    printf("source arg is %s\n", source);

    for (int i = 1; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
}
