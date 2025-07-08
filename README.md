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

## Author
[Your Name]