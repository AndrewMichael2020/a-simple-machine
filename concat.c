#include <stdio.h>
#include <string.h>

int main() {
    // Stack-allocated buffers: memory is managed automatically and released when main() returns
    char str1[100];
    char str2[100];
    char result[200];  // Enough to hold str1 + " & " + str2

    printf("Enter two strings\n");
    printf("[Debug] str1 is allocated at %p, size 100 bytes\n", (void*)str1);
    printf("[Debug] str2 is allocated at %p, size 100 bytes\n", (void*)str2);
    printf("[Debug] result is allocated at %p, size 200 bytes\n", (void*)result);

    // Read two strings
    fgets(str1, sizeof(str1), stdin);
    fgets(str2, sizeof(str2), stdin);

    // Remove trailing newline from both strings
    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';

    // Concatenate
    strcpy(result, str1);
    strcat(result, " & ");
    strcat(result, str2);

    // Output
    printf("%s\n", result);

    // Show memory contents (for demonstration)
    printf("[Debug] str1 contents: '%s'\n", str1);
    printf("[Debug] str2 contents: '%s'\n", str2);
    printf("[Debug] result contents: '%s'\n", result);

    // No need to free memory: stack-allocated arrays are automatically cleaned up
    return 0;
}
