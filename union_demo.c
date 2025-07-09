/*
 * union_demo.c
 *
 * Andrew M's Tutorial: Understanding Unions in C
 *
 * This program demonstrates how a union allows different types to share the same memory.
 * It shows how writing to one member affects the others, with debug output and memory views.
 *
 * Author: Andrew M.
 * Date: July 2025
 */

#include <stdio.h>
#include <string.h>

// Define a union with overlapping members
union Sample {
    int i;
    char ca[4];
    float f;
};

typedef union Sample Sample;

// Utility: Print the raw bytes of the union
void print_bytes(const void* ptr, size_t size) {
    const unsigned char* bytes = (const unsigned char*)ptr;
    printf("Bytes: ");
    for (size_t j = 0; j < size; ++j) {
        printf("%02x ", bytes[j]);
    }
    printf("\n");
}

void run_union_demo() {
    printf("Andrew M's Union Tutorial\n");
    printf("-------------------------\n");
    printf("A union lets you view the same memory as multiple types.\n\n");

    Sample u;

    // Set as int
    u.i = 42;
    printf("After setting u.i = 42:\n");
    printf("  u.i = %08x\n  u.f = %f\n  u.ca = '%s'\n", u.i, u.f, u.ca);
    print_bytes(&u, sizeof(u));
    printf("\n");

    // Set as string
    strcpy(u.ca, "Abc");
    printf("After strcpy(u.ca, 'Abc'):\n");
    printf("  u.i = %08x\n  u.f = %f\n  u.ca = '%s'\n", u.i, u.f, u.ca);
    print_bytes(&u, sizeof(u));
    printf("\n");

    // Set as float
    u.f = 1.0f/3.0f;
    printf("After setting u.f = 1.0/3.0:\n");
    printf("  u.i = %08x\n  u.f = %f\n  u.ca = '", u.i, u.f);
    // Print u.ca as readable chars or hex if not printable
    for (int k = 0; k < 4; ++k) {
        unsigned char c = u.ca[k];
        if (c >= 32 && c <= 126) // printable ASCII
            putchar(c);
        else
            printf("\\x%02x", c);
    }
    printf("'\n");
    print_bytes(&u, sizeof(u));
    printf("\n");

    printf("Notice how all members overlap in memory!\n");
}

int main() {
    run_union_demo();
    return 0;
}

/*
Tutorial Notes:
- A union is like a struct, but all members share the same memory.
- Changing one member changes the underlying bytes for all members.
- Useful for low-level programming, type punning, and memory efficiency.
- Always be careful: only one member should be used at a time!
*/
