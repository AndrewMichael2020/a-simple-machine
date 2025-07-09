/*
 * touring_machine.c
 *
 * A "Touring Machine" is a simplified version of a Turing Machine that operates on a 256-byte memory tape.
 * The machine has a head (position) that starts at 0 and can move left or right, and can write values to memory.
 *
 * This version accepts human-readable instructions and translates them to machine actions.
 *
 * Supported human instructions:
 *   - STORE <value>   : Store <value> at the current position
 *   - RIGHT           : Move the head one position to the right
 *   - LEFT            : Move the head one position to the left
 *   - PRINT           : Print the current memory as a string
 *   - END             : End input and print the memory
 *
 * Example input:
 *   STORE 66
 *   RIGHT
 *   STORE 114
 *   RIGHT
 *   STORE 105
 *   RIGHT
 *   STORE 97
 *   RIGHT
 *   STORE 110
 *   LEFT
 *   LEFT
 *   LEFT
 *   LEFT
 *   STORE 66
 *   END
 *
 * Output:
 *   Memory:
 *   Brian
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MEM_SIZE 256

void print_state(const char *memory, int pos) {
    printf("[Debug] Head at position %d (address %p), memory so far: '%s'\n", pos, (void*)&memory[pos], memory);
}

int main() {
    char memory[MEM_SIZE] = {0};
    int pos = 0;
    char line[128];
    printf("Touring Machine (Human-Friendly Version)\n");
    printf("Instructions:\n");
    printf("  STORE <value>   : Store value (0-255) at current position\n");
    printf("  RIGHT           : Move head right\n");
    printf("  LEFT            : Move head left\n");
    printf("  PRINT           : Print current memory as string\n");
    printf("  END             : End input and print memory\n");
    printf("Example:\n  STORE 66\n  RIGHT\n  STORE 114\n  ...\n  END\n\n");
    while (1) {
        printf("[Input] > ");
        if (!fgets(line, sizeof(line), stdin)) break;
        // Remove trailing newline
        line[strcspn(line, "\n")] = '\0';
        if (strncasecmp(line, "STORE", 5) == 0) {
            int val = -1;
            if (sscanf(line + 5, "%d", &val) == 1 && val >= 0 && val <= 255) {
                printf("[Action] Storing value %d ('%c') at position %d\n", val, (val >= 32 && val <= 126) ? val : '.', pos);
                memory[pos] = (char)val;
                print_state(memory, pos);
            } else {
                printf("[Error] Invalid value for STORE. Must be 0-255.\n");
            }
        } else if (strcasecmp(line, "RIGHT") == 0) {
            if (pos < MEM_SIZE - 1) {
                pos++;
                printf("[Action] Moved head right to position %d\n", pos);
            } else {
                printf("[Warning] Head at rightmost position.\n");
            }
            print_state(memory, pos);
        } else if (strcasecmp(line, "LEFT") == 0) {
            if (pos > 0) {
                pos--;
                printf("[Action] Moved head left to position %d\n", pos);
            } else {
                printf("[Warning] Head at leftmost position.\n");
            }
            print_state(memory, pos);
        } else if (strcasecmp(line, "PRINT") == 0) {
            printf("[Output] Memory base address: %p\n", (void*)memory);
            printf("[Output] Head pointer: %p (position %d)\n", (void*)&memory[pos], pos);
            printf("[Output] Memory as string: '\n");
            for (int i = 0; i < MEM_SIZE && memory[i] != '\0'; ++i) {
                char c = memory[i];
                putchar((c >= 32 && c <= 126) ? c : '.');
            }
            printf("'\n[Output] Memory as hex: ");
            for (int i = 0; i < MEM_SIZE && memory[i] != '\0'; ++i) {
                printf("%02X ", (unsigned char)memory[i]);
            }
            printf("\n[Output] Memory addresses: ");
            for (int i = 0; i < MEM_SIZE && memory[i] != '\0'; ++i) {
                printf("%p ", (void*)&memory[i]);
            }
            printf("\n");
            print_state(memory, pos);
        } else if (strcasecmp(line, "END") == 0) {
            printf("[End] Memory base address: %p\n", (void*)memory);
            printf("[End] Head pointer: %p (position %d)\n", (void*)&memory[pos], pos);
            printf("[End] Final memory as string: '\n");
            for (int i = 0; i < MEM_SIZE && memory[i] != '\0'; ++i) {
                char c = memory[i];
                putchar((c >= 32 && c <= 126) ? c : '.');
            }
            printf("'\n[End] Final memory as hex: ");
            for (int i = 0; i < MEM_SIZE && memory[i] != '\0'; ++i) {
                printf("%02X ", (unsigned char)memory[i]);
            }
            printf("\n[End] Final memory addresses: ");
            for (int i = 0; i < MEM_SIZE && memory[i] != '\0'; ++i) {
                printf("%p ", (void*)&memory[i]);
            }
            printf("\n");
            break;
        } else if (strlen(line) == 0) {
            continue;
        } else {
            printf("[Error] Unknown instruction: '%s'\n", line);
        }
    }
    printf("Memory:\n%s\n", memory);
    // Print hex and addresses for the final memory
    printf("Memory as hex: ");
    for (int i = 0; i < MEM_SIZE && memory[i] != '\0'; ++i) {
        printf("%02X ", (unsigned char)memory[i]);
    }
    printf("\nMemory addresses: ");
    for (int i = 0; i < MEM_SIZE && memory[i] != '\0'; ++i) {
        printf("%p ", (void*)&memory[i]);
    }
    printf("\n");
    return 0;
}
