#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 1000

int main() {
    printf("Start typing to see your input!\n");

    int i = 0, ch = getchar();
    char message[MAX_SIZE];  // Fixed-size array

    for (; (i < MAX_SIZE - 1) && (ch != '\n') && (ch != EOF) ; i++, ch = getchar()) {
        if (ch >= 0 && ch <= 255) {  // Within signed char range
            message[i] = (char)ch;
        } else {
            // Handle out-of-range values
            printf("Error: Invalid input provided!\n");
            return TRUE;
        }
    }

    message[i] = '\0';  // Null terminate the string

    printf("\n");
    printf("%s", message);

    return FALSE;  // Typically return 0 for success
}