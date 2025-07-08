/*
 * preprocessor_examples.c
 *
 * This file demonstrates three common uses of the C preprocessor's #include directive.
 *
 * The C preprocessor runs before compilation. It processes directives (lines starting with #),
 * such as #include, #define, and #ifdef. The #include directive tells the preprocessor to insert
 * the contents of another file at that point in the code. This is used for including standard
 * libraries, user-defined headers, and system headers.
 *
 * Below are three examples, each with a comment explaining why the #include is used.
 *
 * It also demonstrates #ifdef for conditional compilation.
 */

// Example 1: Include the standard input/output library for printf, scanf, etc.
#include <stdio.h>  // Provides input/output functions like printf and scanf

// Example 2: Include the standard library for memory allocation and conversion functions
#include <stdlib.h> // Provides functions like malloc, free, atoi, exit

// Example 3: Include a user-defined header file (would be created by the user)
#include "myheader.h" // Provides user-defined functions, macros, or type definitions

/*
 * Example 4: Using #ifdef for conditional compilation
 *
 * #define EXAMPLE_FLAG at the top of this file (or via compiler -D option)
 * to enable the code inside the #ifdef block. This is useful for debugging,
 * platform-specific code, or optional features.
 */

// Uncomment the next line to enable the block below
// #define EXAMPLE_FLAG

int main() {
    // Using printf from stdio.h
    printf("Hello, world!\n");

    // Using atoi from stdlib.h
    int num = atoi("123");
    printf("Converted string to int: %d\n", num);

    // If myheader.h defined a function, we could call it here (example):
    // my_function();

    // Example of #ifdef usage
#ifdef EXAMPLE_FLAG
    printf("EXAMPLE_FLAG is defined! This code is included.\n");
    printf("(This happened because EXAMPLE_FLAG was defined using '#define EXAMPLE_FLAG' in the code or '-DEXAMPLE_FLAG' in the compiler command.)\n");
    printf("Conditional compilation like this is used in real systems for:\n");
    printf("- Debugging: Enable extra logging or checks only in debug builds.\n");
    printf("- Portability: Include code only for certain operating systems or hardware.\n");
    printf("- Feature toggles: Compile optional features in or out.\n");
#else
    printf("EXAMPLE_FLAG is NOT defined. This code is included instead.\n");
    printf("(This happened because EXAMPLE_FLAG was not defined in the code or compiler command.)\n");
#endif

    return 0;
}

/*
Preprocessor summary:
- #include <...> is used for standard/system headers (searches system paths).
- #include "..." is used for user headers (searches local directory first).
- #ifdef checks if a macro is defined and conditionally includes code.
- #define defines a macro (can be used for flags, constants, etc).
- The preprocessor literally copies the contents of the included file into your source file before compilation.
- This enables code reuse, modularity, and access to library functions.
- Conditional compilation (#ifdef, #ifndef, #endif) is useful for debugging, portability, and feature toggles.
*/
