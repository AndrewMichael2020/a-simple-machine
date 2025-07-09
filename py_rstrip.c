/*
 * py_rstrip.c
 *
 * Demonstrates a function similar to Python's rstrip():
 *
 * rstrip() removes trailing whitespace (spaces, tabs, etc.) from the end of a string.
 * In C, we implement this by modifying the string in place.
 *
 * Usage:
 *   - Only call py_rstrip() with a mutable (non-const) string.
 *   - The function will remove spaces from the end of the string.
 *
 * Example:
 *   Input:  "   Hello   World    "
 *   Output: "   Hello   World"
 */

#include <stdio.h>
#include <string.h>

// Removes trailing spaces from the end of a mutable string (like Python's rstrip)
void py_rstrip(char *s) {
    printf("[Debug] py_rstrip() called with pointer: %p\n", (void*)s);
    if (!s) return;
    size_t len = strlen(s);
    if (len == 0) return;
    size_t i = len - 1;
    // Move backward, replacing trailing spaces with null terminator
    while (i != (size_t)-1 && s[i] == ' ') {
        printf("[Debug] Removing space at s[%zu] (address %p)\n", i, (void*)&s[i]);
        s[i] = '\0';
        if (i == 0) break;
        --i;
    }
    printf("[Debug] py_rstrip() finished. String now ends at address %p\n", (void*)&s[i]);
}

int main() {
    printf("This program demonstrates py_rstrip(), which removes trailing spaces from a string.\n");
    printf("(Like Python's rstrip method, but for C strings.)\n");
    printf("py_rstrip() uses a pointer to the string, so it can modify the memory directly.\n");
    printf("The pointer is just the address of the first character in the array.\n");
    char s1[] = "   Hello   World    ";
    printf("Before: -%s-\n", s1);
    printf("[Debug] s1 is at address: %p\n", (void*)s1);
    py_rstrip(s1);
    printf("After:  -%s-\n", s1);
    return 0;
}
