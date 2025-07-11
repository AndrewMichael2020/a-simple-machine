/*
 * pydict_demo.c
 *
 * Andrew M's Tutorial: Implementing a Subset of Python's dict Class in C
 *
 * This program demonstrates a dynamic dictionary type in C, inspired by Python's dict class.
 * It features put, get, print, and length operations, with detailed debug output.
 *
 * Author: Andrew M.
 * Date: July 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dnode {
    char *key;
    char *value;
    struct dnode *next;
};

struct pydict {
    struct dnode *head;
    struct dnode *tail;
    int count;
};

struct pydict * pydict_new() {
    struct pydict *p = malloc(sizeof(*p));
    p->head = NULL;
    p->tail = NULL;
    p->count = 0;
    printf("[pydict_new] Created new pydict@%p\n", (void*)p);
    return p;
}

void pydict_del(struct pydict* self) {
    printf("[pydict_del] Deleting pydict@%p\n", (void*)self);
    struct dnode *cur, *next;
    cur = self->head;
    while(cur) {
        printf("  [pydict_del] Freeing dnode@%p key='%s' value='%s'\n", (void*)cur, cur->key, cur->value);
        free(cur->key);
        free(cur->value);
        next = cur->next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

void pydict_put(struct pydict *self, const char *key, const char *value) {
    printf("[pydict_put] Setting key='%s' to value='%s'\n", key, value);
    struct dnode *cur = self->head;
    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            printf("  [pydict_put] Key found at dnode@%p, updating value\n", (void*)cur);
            free(cur->value);
            cur->value = strdup(value);
            return;
        }
        cur = cur->next;
    }
    // Not found, add new node
    struct dnode *node = malloc(sizeof(struct dnode));
    if (!node) {
        fprintf(stderr, "[Error] pydict_put: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;
    if (self->tail) {
        self->tail->next = node;
        printf("  [pydict_put] Linked new dnode@%p after tail@%p\n", (void*)node, (void*)self->tail);
    } else {
        self->head = node;
        printf("  [pydict_put] First dnode@%p set as head\n", (void*)node);
    }
    self->tail = node;
    self->count++;
    printf("  [pydict_put] New tail@%p, count=%d\n", (void*)node, self->count);
}

void pydict_print(const struct pydict *self) {
    printf("[");
    struct dnode *cur = self->head;
    int first = 1;
    while (cur) {
        if (!first) printf(", ");
        printf("'%s': '%s'", cur->key, cur->value);
        first = 0;
        cur = cur->next;
    }
    printf("]\n");
}

int pydict_len(const struct pydict *self) {
    printf("[pydict_len] pydict@%p count=%d\n", (void*)self, self->count);
    return self->count;
}

const char *pydict_get(const struct pydict *self, const char *key) {
    printf("[pydict_get] Looking for key='%s' in pydict@%p\n", key, (void*)self);
    struct dnode *cur = self->head;
    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            printf("  [pydict_get] Found at dnode@%p, value='%s'\n", (void*)cur, cur->value);
            return cur->value;
        }
        cur = cur->next;
    }
    printf("  [pydict_get] Not found\n");
    return NULL;
}

int main(void)
{
    struct dnode * cur;
    struct pydict * dct = pydict_new();

    setvbuf(stdout, NULL, _IONBF, 0);  /* Internal */

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

    printf("\nDump\n");
    for(cur = dct->head; cur != NULL ; cur = cur->next ) {
        printf("%s=%s\n", cur->key, cur->value);
    }

    pydict_del(dct);
    return 0;
}

/*
Tutorial Notes:
- This struct and functions mimic a subset of Python's dict class in C.
- The dictionary is a singly linked list of key-value pairs.
- All memory is managed with malloc/free.
- This is a foundation for more advanced dict types in C.
*/
