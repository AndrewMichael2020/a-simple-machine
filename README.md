# Andrew M's Simple Interpreter and Classic CS Concepts in C

This repository is a collection of educational C programs by Andrew M. that demonstrate classic computer science concepts, including memory interpreters, recursion, stack usage, the C preprocessor, string manipulation, and a human-friendly Touring Machine. Each program is self-contained and includes detailed prompts, debug output, and historical context.

---

## Table of Contents
- [Simple Machine Interpreter](#simple-machine-interpreter)
- [C Preprocessor Examples](#c-preprocessor-examples)
- [Simplest Recursive Function: sumseries](#simplest-recursive-function-sumseries)
- [Reverse Polish Notation (RPN) Calculator](#reverse-polish-notation-rpn-calculator)
- [Implementing Python Functions in C: py_rstrip and py_lstrip](#implementing-python-functions-in-c-py_rstrip-and-py_lstrip)
- [Touring Machine (Human-Friendly Turing Machine)](#touring-machine-human-friendly-turing-machine)
- [Build and Cleanup](#build-and-cleanup)

---

## Simple Machine Interpreter

A minimalistic memory interpreter inspired by FORTRAN-style pseudocode (Fortrun).

### Features
- Simulates a 256-byte memory array, initialized to zero.
- Accepts instructions in the form:

      ADDR OPCODE VALUE

  where:
  - **ADDR**   = memory address (0-255)
  - **OPCODE** = '=' (assign), '+' (add), '-' (subtract)
  - **VALUE**  = integer value (0-255)
- Supports comments (lines starting with `*`) and exit (`X`).
- After each instruction, prints the memory in ASCII and hex views.

### Fortrun Ties
The memory model and operations are inspired by classic FORTRAN pseudocode, as shown in the comments of `dump_memory()` in the code. The interpreter mimics the way FORTRAN would manipulate a character array for simple memory operations.

### Example: Storing a String
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

### Usage
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

## C Preprocessor Examples

Demonstrates the use of the C preprocessor, including `#include`, `#define`, and `#ifdef`.

### What is the C Preprocessor?
The C preprocessor runs before compilation. It processes directives (lines starting with #), such as `#include`, `#define`, and `#ifdef`. The `#include` directive tells the preprocessor to insert the contents of another file at that point in the code. This enables code reuse, modularity, and access to library functions.

### What does `preprocessor_examples.c` show?
- How to include standard headers (e.g., `<stdio.h>`, `<stdlib.h>`)
- How to include a user-defined header (e.g., `"myheader.h"`)
- How to use `#ifdef` and `#define` for conditional compilation
- Comments in the code explain why each include is used

### How to Build and Run
Build the example with:

    make preprocessor_examples

Run it with:

    ./preprocessor_examples

You should see output like:

    Hello, world!
    Converted string to int: 123
    EXAMPLE_FLAG is NOT defined. This code is included instead.

### How to See the Preprocessed C Code
To see the C code after the preprocessor has run (with all includes expanded), use:

    gcc -E preprocessor_examples.c -o preprocessor_examples.i

This will create a file `preprocessor_examples.i` containing the fully expanded C code. You can open this file in your editor or view the first lines with:

    head -40 preprocessor_examples.i

### How to Show #ifdef Output
To see how `#ifdef` changes the compiled program, try compiling and running with and without the flag:

**Default (EXAMPLE_FLAG not defined):**

    make preprocessor_examples
    ./preprocessor_examples

**With EXAMPLE_FLAG defined:**

    gcc -DEXAMPLE_FLAG preprocessor_examples.c -o preprocessor_examples
    ./preprocessor_examples

This demonstrates how #ifdef and #define can be used to include or exclude code at compile time.

---

## Simplest Recursive Function: sumseries

Demonstrates recursion and stack usage in C with the function `sumseries`.

### What is Recursion?
Recursion is when a function calls itself to solve a smaller instance of the same problem. Each recursive call is placed on the call stack, and the stack unwinds as base cases are reached.

### What does sumseries do?
- Computes the sum of all numbers from 1 to n (inclusive).
- If n < 1, returns 0.
- If n > 100, returns -1 (to avoid stack overflow).
- Prints the stack depth and value at each call and return, so you can see how the stack grows and shrinks.

### Example Output
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

### How to Build and Run
Build with:

    make simplest_recursive_function

Run with:

    ./simplest_recursive_function

You will see output for several test values, showing the stack in action for each call.

### Why is the Stack Important?
Each recursive call is placed on the stack. If the recursion is too deep (e.g., n > 100), the program returns -1 to avoid stack overflow. This demonstrates how recursion uses the stack in C.

---

## Reverse Polish Notation (RPN) Calculator

Implements a simple Reverse Polish Notation (RPN) calculator in C.

### What is RPN?
Reverse Polish Notation (postfix notation) is a mathematical notation in which every operator follows all of its operands. For example, the infix expression:

    (3 + 4) * 2

In RPN becomes:

    3 4 + 2 *

RPN is evaluated left to right:
- Push operands onto a stack.
- When an operator is encountered, pop the top two operands, apply the operator, and push the result back.

### Historical Note
- **RPN** was popularized by early Hewlett-Packard calculators (HP-35, HP-41C, etc.) and is still used in some scientific calculators today for its efficiency and lack of parentheses.
- **Memory interpreters** and direct memory manipulation were common in early programming languages like FORTRAN and in assembly language programming, where programmers often worked directly with memory addresses and values.
- **Assemblers** and low-level languages often used similar stack-based or memory-based approaches for evaluating expressions and managing data.

### Usage
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

### Example Inputs and Outputs

Input:

    3 4 + 2 *

Output:

    Result: 14

Input:

    15 7 1 1 + - / 3 * 2 1 1 + + -

Output:

    Result: 5

### Input/Output Expectations
- Input: A single line, space-separated, containing integers and operators (+, -, *, /).
- Output: The result of the RPN expression, or an error message if the input is invalid.

### Why a Stack?
A stack is the ideal data structure for RPN evaluation because it allows pushing operands and popping them for operations in the correct order (Last-In-First-Out).

---

## Implementing Python Functions in C: py_rstrip and py_lstrip

Demonstrates how to remove whitespace from the end or beginning of a string in C, similar to Python's `rstrip()` and `lstrip()`.

### py_rstrip
- Removes trailing spaces from a mutable string.
- Modifies the string in place using pointers.
- Prints debug information showing how memory is changed.

### py_lstrip
- Removes leading whitespace (spaces, tabs, newlines) from a mutable string.
- Modifies the string in place using pointers and `memmove`.
- Prints debug information showing how memory is changed.

---

## Touring Machine (Human-Friendly Turing Machine)

A simplified, interactive Turing Machine that operates on a 256-byte memory tape. Accepts human-friendly instructions and prints detailed debug output.

### Features
- Memory: 256 bytes, all initialized to zero.
- Head: Keeps track of the current position (starts at 0).
- Instructions:
  - `STORE <value>`: Store value (0-255) at the current position.
  - `RIGHT`: Move the head right.
  - `LEFT`: Move the head left.
  - `PRINT`: Print the current memory as a string, hex, and addresses.
  - `END`: End input and print the memory.
- Prints the memory, hex values, and addresses after each command.
- Shows the head position and address in debug output.

### Example Session
```
[Input] > STORE 66
[Action] Storing value 66 ('B') at position 0
[Debug] Head at position 0 (address 0x7fff7423c680), memory so far: 'B'
[Input] > RIGHT
[Action] Moved head right to position 1
[Debug] Head at position 1 (address 0x7fff7423c681), memory so far: 'B'
[Input] > STORE 114
[Action] Storing value 114 ('r') at position 1
[Debug] Head at position 1 (address 0x7fff7423c681), memory so far: 'Br'
[Input] > END
[End] Memory base address: 0x7fff7423c680
[End] Head pointer: 0x7fff7423c681 (position 1)
[End] Final memory as string: '
Br'
[End] Final memory as hex: 42 72 
[End] Final memory addresses: 0x7fff7423c680 0x7fff7423c681 
Memory:
Br
Memory as hex: 42 72 
Memory addresses: 0x7fff7423c680 0x7fff7423c681 
```

---

## Build and Cleanup

To build all programs, use:

    make

To build a specific program, use:

    make <target>

For example:

    make touring_machine

To clean up all executables, use:

    make clean

---

## Python-like Dictionary Class in C: pydict_demo.c

This tutorial demonstrates a dynamic dictionary type in C, inspired by Python's `dict` class. It supports put, get, print, and length operations, and includes detailed debug output to illustrate memory management and dictionary operations.

- `pydict_put(dct, key, value)`: Add or update a key-value pair.
- `pydict_get(dct, key)`: Retrieve the value for a key (returns NULL if not found).
- `pydict_print(dct)`: Print the dictionary contents in Python-like format.
- `pydict_len(dct)`: Return the number of key-value pairs.
- `pydict_del(dct)`: Free all memory used by the dictionary.

Example usage:

```
struct pydict * dct = pydict_new();
pydict_put(dct, "z", "Catch phrase");
pydict_print(dct);
pydict_put(dct, "z", "W");
pydict_print(dct);
pydict_put(dct, "y", "B");
pydict_put(dct, "c", "C");
pydict_put(dct, "a", "D");
pydict_print(dct);
printf("Length =%d\n",pydict_len(dct));
printf("z=%s\n", pydict_get(dct, "z"));
printf("x=%s\n", pydict_get(dct, "x"));
pydict_del(dct);
```

This is a foundation for more advanced dictionary types in C, and demonstrates how to manage key-value pairs and memory safely.

---

## Encapsulated Python-like Dictionary Class in C: map_encapsulation_demo.c

This tutorial demonstrates encapsulation and OOP-like method binding in C, inspired by Python's `dict` class and dunder naming conventions. The `Map` struct uses function pointers to simulate methods, with all internal data hidden and only dunder-named methods accessible.

- `Map_new()`: Create a new Map object.
- `__Map_put(map, key, value)`: Add or update a key-value pair.
- `__Map_get(map, key)`: Retrieve the value for a key (returns NULL if not found).
- `__Map_size(map)`: Return the number of key-value pairs.
- `__Map_dump(map)`: Print the dictionary contents in Python-like format.
- `__Map_del(map)`: Free all memory used by the Map.

### Example usage:

```c
struct Map * map = Map_new();
__Map_put(map, "z", "Catch phrase");
__Map_dump(map);
__Map_put(map, "z", "W");
__Map_dump(map);
__Map_put(map, "y", "B");
__Map_put(map, "c", "C");
__Map_put(map, "a", "D");
__Map_dump(map);
printf("Length =%d\n", __Map_size(map));
printf("z=%s\n", __Map_get(map, "z"));
printf("x=%s\n", __Map_get(map, "x"));
__Map_del(map);
```

This example matches the output and usage of the Python-like dict class, but with all internals hidden and only dunder-named methods exposed. The code demonstrates encapsulation, method pointers, and introspective printing for educational clarity.

---

Each program is self-contained and demonstrates a key concept in C and computer science. Explore the code and run the examples to deepen your understanding!
