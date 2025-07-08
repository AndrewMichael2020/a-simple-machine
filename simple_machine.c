
/*
 * simple_machine.c
 *
 * A minimalistic memory interpreter inspired by FORTRAN-style pseudocode (Fortrun).
 *
 * Functionality:
 *   - Simulates a 256-byte memory array, initialized to zero.
 *   - Accepts instructions from the user in the form: ADDR OPCODE VALUE
 *     where:
 *       ADDR   = memory address (0-255)
 *       OPCODE = '=' (assign), '+' (add), '-' (subtract)
 *       VALUE  = integer value (0-255)
 *   - Supports comments (lines starting with '*') and exit (X).
 *   - After each instruction, prints the memory in ASCII and hex views.
 *
 * Fortrun ties:
 *   - The memory model and operations are inspired by classic FORTRAN pseudocode,
 *     as shown in the dump_memory() comments.
 *   - Example: To store the ASCII string "I am Andrew" in memory:
 *       0 = 73
 *       1 = 32
 *       2 = 97
 *       3 = 109
 *       4 = 32
 *       5 = 65
 *       6 = 110
 *       7 = 100
 *       8 = 114
 *       9 = 101
 *      10 = 119
 *      11 = 0
 *     This will result in memory containing the null-terminated string "I am Andrew".
 *
 * Author: [Your Name]
 * Date: 2025
 */

#include <stdio.h>

#define MEM_SIZE 256

char memory[MEM_SIZE] = {0};  // global memory initialized to 0

void dump_memory() {
// Prints the current state of memory in ASCII and hex views.
    printf("\n[Memory Dump - ASCII View]:\n%s\n", memory);
    printf("\n[Memory Dump - Hex View]:\n");

    int i, j;
    for (i = 0; i < 64; i += 16) {
        printf("%02X: ", i);
        for (j = 0; j < 16; ++j) {
            printf("%02X ", (unsigned char)memory[i + j]);
        }
        printf("\n");
    }

    /*
    C FORTRAN-style pseudocode simulation (Fortrun)

          CHARACTER*256 MEMORY
          DATA MEMORY /256*' '/

    C     Equivalent of 5 = 65
          MEMORY(6:6) = CHAR(65)

    C     Equivalent of 5 + 1
          I = ICHAR(MEMORY(6:6)) + 1
          MEMORY(6:6) = CHAR(MOD(I,256))

    C     Equivalent of 5 - 2
          I = ICHAR(MEMORY(6:6)) - 2
          IF (I .LT. 0) I = I + 256
          MEMORY(6:6) = CHAR(I)

    C     Output final memory
          PRINT *, MEMORY
    */
}

void assign(int addr, int val) {
// Assigns VALUE to memory[ADDR] if within valid range.
    printf("[assign] memory[%d] = %d\n", addr, val);
    if (addr >= 0 && addr < MEM_SIZE && val >= 0 && val <= 255)
        memory[addr] = (char)val;
}

void add(int addr, int val) {
// Adds VALUE to memory[ADDR] (modulo 256) if within valid range.
    int before = memory[addr];
    int after = (before + val) % 256;
    printf("[add] memory[%d] = %d + %d = %d\n", addr, before, val, after);
    if (addr >= 0 && addr < MEM_SIZE && val >= 0 && val <= 255)
        memory[addr] = (char)after;
}

void subtract(int addr, int val) {
// Subtracts VALUE from memory[ADDR] (modulo 256) if within valid range.
    int before = memory[addr];
    int after = (before - val + 256) % 256;
    printf("[sub] memory[%d] = %d - %d = %d\n", addr, before, val, after);
    if (addr >= 0 && addr < MEM_SIZE && val >= 0 && val <= 255)
        memory[addr] = (char)after;
}

int main() {
// Main interpreter loop: reads user instructions, parses, executes, and dumps memory.
    char line[256];
    char opcode;
    int count, address, value;

    while (1) {
        printf("> Enter instruction (ADDR OPCODE VALUE), comment (*...), or X to exit:\n");
        printf("    ADDR   = memory address (0-255)\n");
        printf("    OPCODE = = (assign), + (add), - (subtract)\n");
        printf("    VALUE  = integer value (0-255)\n");
        printf("  Example: 5 = 65   or   10 + 1   or   * this is a comment\n");
        printf("> ");
        fflush(stdout);
        if (fgets(line, 256, stdin) == NULL) break;
        printf("\n>>> Line: %s", line);

        if (line[0] == 'X') break;
        if (line[0] == '*') {
            printf("[comment] %s", line);
            continue;
        }

        count = sscanf(line, "%d %c %d", &address, &opcode, &value);
        if (count != 3) {
            printf("[skip] malformed instruction.\n");
            continue;
        }

        switch (opcode) {
            case '=':
                assign(address, value);
                break;
            case '+':
                add(address, value);
                break;
            case '-':
                subtract(address, value);
                break;
            default:
                printf("[error] unknown opcode: %c\n", opcode);
        }

        dump_memory();
    }

    printf("\n[Final Memory State]\n");
    dump_memory();
    return 0;
}
