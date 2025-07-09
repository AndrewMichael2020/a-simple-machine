/*
 * py_lstrip.c
 *
 * Demonstrates a function similar to Python's lstrip():
 *
 * lstrip() removes leading whitespace (spaces, tabs, newlines) from the beginning of a string.
 * In C, we implement this by shifting the string contents left in place.
 *
 * Usage:
 *   - Only call py_lstrip() with a mutable (non-const) string.
 *   - The function will remove whitespace from the beginning of the string.
 *
 * Example:
 *   Input:  " \t\n   Hello   World    "
 *   Output: "Hello   World    "
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Removes leading whitespace from the beginning of a mutable string (like Python's lstrip)
void py_lstrip(char *s) {
    printf("[Debug] py_lstrip() called with pointer: %p\n", (void*)s);
    if (!s) return;
    size_t len = strlen(s);
    if (len == 0) return;
    size_t i = 0;
    // Find first non-whitespace character
    while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')) {
        printf("[Debug] Skipping whitespace at s[%zu] (address %p, char '%c')\n", i, (void*)&s[i], s[i]);
        ++i;
    }
    if (i > 0) {
        printf("[Debug] Shifting string left by %zu bytes\n", i);
        memmove(s, s + i, len - i + 1); // +1 to move the null terminator
    }
    printf("[Debug] py_lstrip() finished. String now starts at address %p\n", (void*)s);
}

int main() {
    printf("This program demonstrates py_lstrip(), which removes leading whitespace from a string.\n");
    printf("(Like Python's lstrip method, but for C strings.)\n");
    printf("py_lstrip() uses a pointer to the string, so it can modify the memory directly.\n");
    printf("The pointer is just the address of the first character in the array.\n");
    char s1[] = " \t\n   Hello   World    ";
    printf("Before: -%s-\n", s1);
    printf("[Debug] s1 is at address: %p\n", (void*)s1);
    py_lstrip(s1);
    printf("After:  -%s-\n", s1);
    return 0;
}
