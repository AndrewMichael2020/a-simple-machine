/*
 * rpn_calculator.c
 *
 * A simple Reverse Polish Notation (RPN) calculator in C.
 *
 * What is RPN?
 *   Reverse Polish Notation (postfix notation) is a mathematical notation in which every operator follows all of its operands.
 *   For example, the infix expression: (3 + 4) * 2
 *   In RPN: 3 4 + 2 *
 *
 *   RPN is evaluated left to right:
 *     - Push operands onto a stack.
 *     - When an operator is encountered, pop the top two operands, apply the operator, and push the result back.
 *
 * Example Inputs and Outputs:
 *   Input: 3 4 + 2 *\n
 *   Output: Result: 14
 *
 *   Input: 15 7 1 1 + - / 3 * 2 1 1 + + -\n
 *   Output: Result: 5
 *
 * Usage:
 *   - Enter a space-separated RPN expression (e.g., "3 4 + 2 *").
 *   - Supported operators: +, -, *, /
 *   - Operands and results are integers.
 *   - The calculator prints the result or an error message.
 *
 * The calculator uses a stack to evaluate the expression.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK 100
#define MAX_LINE 256

// Stack implementation for integer values
typedef struct {
    int data[MAX_STACK];
    int top;
} Stack;

// Initialize the stack
void init(Stack *s) { s->top = -1; }
// Returns 1 if the stack is empty, 0 otherwise
int is_empty(Stack *s) { return s->top == -1; }
// Returns 1 if the stack is full, 0 otherwise
int is_full(Stack *s) { return s->top == MAX_STACK - 1; }
// Pushes a value onto the stack. Returns 1 on success, 0 if full.
int push(Stack *s, int val) {
    if (is_full(s)) return 0;
    s->data[++(s->top)] = val;
    return 1;
}
// Pops a value from the stack into *val. Returns 1 on success, 0 if empty.
int pop(Stack *s, int *val) {
    if (is_empty(s)) return 0;
    *val = s->data[(s->top)--];
    return 1;
}

int main() {
    char line[MAX_LINE];
    Stack stack;
    init(&stack);
    printf("Reverse Polish Notation (RPN) Calculator\n");
    printf("--------------------------------------\n");
    printf("Enter a space-separated RPN expression.\n");
    printf("  Example: 3 4 + 2 *\n");
    printf("  Example: 15 7 1 1 + - / 3 * 2 1 1 + + -\n");
    printf("Supported operators: +  -  *  /\n");
    printf("Operands and results are integers.\n");
    printf("> ");
    if (!fgets(line, MAX_LINE, stdin)) return 1;

    char *token = strtok(line, " \t\n");
    while (token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&stack, atoi(token));
        } else if (strlen(token) == 1 && strchr("+-*/", token[0])) {
            int b, a;
            if (!pop(&stack, &b) || !pop(&stack, &a)) {
                printf("Error: Not enough operands for '%s'\n", token);
                return 1;
            }
            int result;
            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("Error: Division by zero\n");
                        return 1;
                    }
                    result = a / b; break;
                default:
                    printf("Error: Unknown operator '%s'\n", token);
                    return 1;
            }
            push(&stack, result);
        } else {
            printf("Error: Invalid token '%s'\n", token);
            return 1;
        }
        token = strtok(NULL, " \t\n");
    }
    if (stack.top == 0) {
        printf("Result: %d\n", stack.data[0]);
    } else {
        printf("Error: Stack has %d items after evaluation (should be 1)\n", stack.top + 1);
        return 1;
    }
    return 0;
}
