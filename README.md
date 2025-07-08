# Simple Machine Interpreter

This project implements a minimalistic memory interpreter inspired by FORTRAN-style pseudocode (Fortrun).

## Features
- Simulates a 256-byte memory array, initialized to zero.
- Accepts instructions from the user in the form:

      ADDR OPCODE VALUE

  where:
  - **ADDR**   = memory address (0-255)
  - **OPCODE** = '=' (assign), '+' (add), '-' (subtract)
  - **VALUE**  = integer value (0-255)
- Supports comments (lines starting with `*`) and exit (`X`).
- After each instruction, prints the memory in ASCII and hex views.

## Fortrun Ties
The memory model and operations are inspired by classic FORTRAN pseudocode, as shown in the comments of `dump_memory()` in the code. The interpreter mimics the way FORTRAN would manipulate a character array for simple memory operations.

## Example: Storing a String
To store the ASCII string `I am Andrew` in memory, enter the following instructions:

```
0 = 73
1 = 32
2 = 97
3 = 109
4 = 32
5 = 65
6 = 110
7 = 100
8 = 114
9 = 101
10 = 119
11 = 0
```

This will result in memory containing the null-terminated string `I am Andrew`.

## Usage
Run the program and follow the prompt:

```
> Enter instruction (ADDR OPCODE VALUE), comment (*...), or X to exit:
    ADDR   = memory address (0-255)
    OPCODE = = (assign), + (add), - (subtract)
    VALUE  = integer value (0-255)
  Example: 5 = 65   or   10 + 1   or   * this is a comment
> 
```

- Enter instructions as shown above.
- Use `*` at the start of a line for comments.
- Enter `X` to exit and see the final memory state.

---

# Reverse Polish Notation (RPN) Calculator

This project also includes a simple Reverse Polish Notation (RPN) calculator implemented in C.

## What is RPN?
Reverse Polish Notation (postfix notation) is a mathematical notation in which every operator follows all of its operands. For example, the infix expression:

    (3 + 4) * 2

In RPN becomes:

    3 4 + 2 *

RPN is evaluated left to right:
- Push operands onto a stack.
- When an operator is encountered, pop the top two operands, apply the operator, and push the result back.

## Historical Note
- **RPN** was popularized by early Hewlett-Packard calculators (HP-35, HP-41C, etc.) and is still used in some scientific calculators today for its efficiency and lack of parentheses.
- **Memory interpreters** and direct memory manipulation were common in early programming languages like FORTRAN and in assembly language programming, where programmers often worked directly with memory addresses and values.
- **Assemblers** and low-level languages often used similar stack-based or memory-based approaches for evaluating expressions and managing data.

## Usage
Build the calculator with:

    make rpn_calculator

Run it with:

    ./rpn_calculator

You will see a prompt like:

    Reverse Polish Notation (RPN) Calculator
    --------------------------------------
    Enter a space-separated RPN expression.
      Example: 3 4 + 2 *
      Example: 15 7 1 1 + - / 3 * 2 1 1 + + -
    Supported operators: +  -  *  /
    Operands and results are integers.
    >

## Example Inputs and Outputs

Input:

    3 4 + 2 *

Output:

    Result: 14

Input:

    15 7 1 1 + - / 3 * 2 1 1 + + -

Output:

    Result: 5

## Input/Output Expectations
- Input: A single line, space-separated, containing integers and operators (+, -, *, /).
- Output: The result of the RPN expression, or an error message if the input is invalid.

## Why a Stack?
A stack is the ideal data structure for RPN evaluation because it allows pushing operands and popping them for operations in the correct order (Last-In-First-Out).

## Author
[Your Name]

---

# C Preprocessor Examples

This project also includes a demonstration of the C preprocessor's #include directive in `preprocessor_examples.c`.

## What is the C Preprocessor?
The C preprocessor runs before compilation. It processes directives (lines starting with #), such as `#include`, `#define`, and `#ifdef`. The `#include` directive tells the preprocessor to insert the contents of another file at that point in the code. This enables code reuse, modularity, and access to library functions.

## What does `preprocessor_examples.c` show?
- How to include standard headers (e.g., `<stdio.h>`, `<stdlib.h>`)
- How to include a user-defined header (e.g., `"myheader.h"`)
- Comments in the code explain why each include is used

## How to Build and Run
Build the example with:

    make preprocessor_examples

Run it with:

    ./preprocessor_examples

You should see output like:

    Hello, world!
    Converted string to int: 123

## How to See the Preprocessed C Code
To see the C code after the preprocessor has run (with all includes expanded), use:

    gcc -E preprocessor_examples.c -o preprocessor_examples.i

This will create a file `preprocessor_examples.i` containing the fully expanded C code. You can open this file in your editor or view the first lines with:

    head -40 preprocessor_examples.i

This is useful for understanding what the compiler actually sees after preprocessing.

## How to Show #ifdef Output
To see how `#ifdef` changes the compiled program, try compiling and running with and without the flag:

**Default (EXAMPLE_FLAG not defined):**

    make preprocessor_examples
    ./preprocessor_examples

Output:

    Hello, world!
    Converted string to int: 123
    EXAMPLE_FLAG is NOT defined. This code is included instead.

**With EXAMPLE_FLAG defined:**

    gcc -DEXAMPLE_FLAG preprocessor_examples.c -o preprocessor_examples
    ./preprocessor_examples

Output:

    Hello, world!
    Converted string to int: 123
    EXAMPLE_FLAG is defined! This code is included.

This demonstrates how #ifdef and #define can be used to include or exclude code at compile time.

---

# Simplest Recursive Function: sumseries

This project includes a demonstration of recursion in C with the function `sumseries`.

## What is Recursion?
Recursion is when a function calls itself to solve a smaller instance of the same problem. Each recursive call is placed on the call stack, and the stack unwinds as base cases are reached.

## What does sumseries do?
- Computes the sum of all numbers from 1 to n (inclusive).
- If n < 1, returns 0.
- If n > 100, returns -1 (to avoid stack overflow).
- Prints the stack depth and value at each call and return, so you can see how the stack grows and shrinks.

## Example Output
```
Calling sumseries(5):
Entering sumseries(n=5) at stack depth 1
Entering sumseries(n=4) at stack depth 2
Entering sumseries(n=3) at stack depth 3
Entering sumseries(n=2) at stack depth 4
Entering sumseries(n=1) at stack depth 5
Base case: n == 1, returning 1 at depth 5
Returning 3 from sumseries(n=2) at depth 4
Returning 6 from sumseries(n=3) at depth 3
Returning 10 from sumseries(n=4) at depth 2
Returning 15 from sumseries(n=5) at depth 1
sumseries(5) = 15
```

## How to Build and Run
Build with:

    gcc simplest_recursive_function.c -o simplest_recursive_function

Run with:

    ./simplest_recursive_function

You will see output for several test values, showing the stack in action for each call.

## Why is the Stack Important?
Each recursive call is placed on the stack. If the recursion is too deep (e.g., n > 100), the program returns -1 to avoid stack overflow. This demonstrates how recursion uses the stack in C.