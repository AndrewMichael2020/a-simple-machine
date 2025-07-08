/*
 * simplest_recursive_function.c
 *
 * Demonstrates a simple recursive function (sumseries) in C.
 *
 * sumseries(n):
 *   - Returns the sum of all numbers from 1 to n (inclusive).
 *   - If n < 1, returns 0.
 *   - If n > 100, returns -1 to avoid stack overflow.
 *   - Prints the call stack at each step to show recursion in action.
 *
 * This is a classic example of recursion, where the function calls itself with a smaller argument.
 * The stack is used to keep track of each function call until the base case is reached.
 */

#include <stdio.h>

/**
 * Recursively computes the sum of all numbers from 1 to n.
 * Returns 0 if n < 1, -1 if n > 100 (to avoid stack overflow).
 * Prints the stack depth and value at each call and return.
 */
int sumseries(int n, int depth) {
    printf("Entering sumseries(n=%d) at stack depth %d\n", n, depth);
    if (n < 1) {
        printf("Base case: n < 1, returning 0 at depth %d\n", depth);
        return 0;
    }
    if (n > 100) {
        printf("Error: n > 100, returning -1 at depth %d\n", depth);
        return -1;
    }
    if (n == 1) {
        printf("Base case: n == 1, returning 1 at depth %d\n", depth);
        return 1;
    }
    int result = n + sumseries(n - 1, depth + 1);
    printf("Returning %d from sumseries(n=%d) at depth %d\n", result, n, depth);
    return result;
}

int main() {
    int test_values[] = {0, 1, 5, 10, 101};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    for (int i = 0; i < num_tests; ++i) {
        int n = test_values[i];
        printf("\nCalling sumseries(%d):\n", n);
        int sum = sumseries(n, 1);
        printf("sumseries(%d) = %d\n", n, sum);
    }
    return 0;
}
