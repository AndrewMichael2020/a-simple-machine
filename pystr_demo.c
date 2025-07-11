/*
 * pystr_demo.c
 *
 * Andrew M's Tutorial: Implementing a Subset of Python's str Class in C
 *
 * This program demonstrates a dynamic string type in C, inspired by Python's str class.
 * It features dynamic buffer management, append, and length tracking, with detailed debug output.
 *
 * Author: Andrew M.
 * Date: July 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pystr {
    int length;
    int alloc; /* the length of *data */
    char *data;
};

typedef struct pystr pystr;

/**
 * Allocates a new pystr with a 10-character buffer.
 */
pystr *pystr_new() {
    printf("[pystr_new] Called to create a new pystr object\n");
    pystr *s = (pystr *)malloc(sizeof(pystr));
    if (!s) {
        fprintf(stderr, "[Error] pystr_new: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    s->length = 0;
    s->alloc = 10;
    s->data = (char *)malloc(s->alloc);
    if (!s->data) {
        fprintf(stderr, "[Error] pystr_new: malloc for data failed\n");
        free(s);
        exit(EXIT_FAILURE);
    }
    s->data[0] = '\0';
    printf("[pystr_new] pystr struct allocated at %p\n", (void*)s);
    printf("[pystr_new] data buffer allocated at %p (alloc=%d)\n", (void*)s->data, s->alloc);
    return s;
}

/**
 * Appends a C string to the pystr, expanding buffer as needed.
 */
void pystr_append(pystr *s, const char *suffix) {
    printf("[pystr_append] Called with suffix='%s'\n", suffix);
    printf("[pystr_append] Current length=%d, alloc=%d, data='%s'\n", s->length, s->alloc, s->data);
    int addlen = strlen(suffix);
    int newlen = s->length + addlen;
    if (newlen + 1 > s->alloc) {
        int newalloc = s->alloc;
        while (newlen + 1 > newalloc) newalloc += 10;
        printf("[pystr_append] Buffer too small, reallocating from %d to %d bytes\n", s->alloc, newalloc);
        char *newdata = (char *)realloc(s->data, newalloc);
        if (!newdata) {
            fprintf(stderr, "[Error] pystr_append: realloc failed\n");
            exit(EXIT_FAILURE);
        }
        printf("[pystr_append] Buffer reallocated at %p\n", (void*)newdata);
        s->data = newdata;
        s->alloc = newalloc;
    }
    strcpy(s->data + s->length, suffix);
    s->length = newlen;
    printf("[pystr_append] After append: length=%d, alloc=%d, data='%s'\n", s->length, s->alloc, s->data);
}

/**
 * Frees the pystr and its buffer.
 */
void pystr_free(pystr *s) {
    if (s) {
        printf("[pystr_free] Called for pystr@%p\n", (void*)s);
        printf("[pystr_free] Freeing data buffer at %p\n", (void*)s->data);
        free(s->data);
        printf("[pystr_free] Freeing pystr struct at %p\n", (void*)s);
        free(s);
    }
}

/**
 * Prints the pystr's contents and metadata.
 */
void pystr_dump(const pystr *s) {
    printf("[pystr_dump] pystr@%p\n", (void*)s);
    printf("            |-- length = %d\n", s->length);
    printf("            |-- alloc  = %d\n", s->alloc);
    printf("            |-- data   = '%s'\n", s->data);
    printf("            |-- data buffer address = %p\n", (void*)s->data);
}

int main() {
    pystr *s = pystr_new();
    pystr_dump(s);
    pystr_append(s, "Hello");
    pystr_dump(s);
    pystr_append(s, ", world!");
    pystr_dump(s);
    pystr_append(s, " This is a long string to test buffer expansion.");
    pystr_dump(s);
    pystr_free(s);
    return 0;
}

/*
Tutorial Notes:
- This struct and functions mimic a subset of Python's str class in C.
- The buffer grows in chunks of 10 bytes as needed (like Python's dynamic resizing).
- All memory is managed with malloc/realloc/free.
- This is a foundation for more advanced string types in C.
*/
