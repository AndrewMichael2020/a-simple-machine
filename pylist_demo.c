/*
 * pylist_demo.c
 *
 * Andrew M's Tutorial: Implementing a Subset of Python's list Class in C
 *
 * This program demonstrates a dynamic list type in C, inspired by Python's list class.
 * It features append, print, length, and index operations, with detailed debug output.
 *
 * Author: Andrew M.
 * Date: July 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lnode {
    char *text;
    struct lnode *next;
};

struct pylist {
    struct lnode *head;
    struct lnode *tail;
    int count;
};

struct pylist * pylist_new() {
    struct pylist *p = malloc(sizeof(*p));
    p->head = NULL;
    p->tail = NULL;
    p->count = 0;
    printf("[pylist_new] Created new pylist@%p\n", (void*)p);
    return p;
}

void pylist_del(struct pylist* self) {
    printf("[pylist_del] Deleting pylist@%p\n", (void*)self);
    struct lnode *cur, *next;
    cur = self->head;
    while(cur) {
        printf("  [pylist_del] Freeing lnode@%p text='%s'\n", (void*)cur, cur->text);
        free(cur->text);
        next = cur->next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

void pylist_append(struct pylist *self, const char *text) {
    printf("[pylist_append] Appending '%s' to pylist@%p\n", text, (void*)self);
    struct lnode *node = malloc(sizeof(struct lnode));
    if (!node) {
        fprintf(stderr, "[Error] pylist_append: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    node->text = strdup(text);
    node->next = NULL;
    if (self->tail) {
        self->tail->next = node;
        printf("  [pylist_append] Linked new node@%p after tail@%p\n", (void*)node, (void*)self->tail);
    } else {
        self->head = node;
        printf("  [pylist_append] First node@%p set as head\n", (void*)node);
    }
    self->tail = node;
    self->count++;
    printf("  [pylist_append] New tail@%p, count=%d\n", (void*)node, self->count);
}

void pylist_print(const struct pylist *self) {
    printf("[");
    struct lnode *cur = self->head;
    int first = 1;
    while (cur) {
        if (!first) printf(", ");
        printf("'%s'", cur->text);
        first = 0;
        cur = cur->next;
    }
    printf("]\n");
}

int pylist_len(const struct pylist *self) {
    printf("[pylist_len] pylist@%p count=%d\n", (void*)self, self->count);
    return self->count;
}

int pylist_index(const struct pylist *self, const char *text) {
    printf("[pylist_index] Searching for '%s' in pylist@%p\n", text, (void*)self);
    struct lnode *cur = self->head;
    int idx = 0;
    while (cur) {
        if (strcmp(cur->text, text) == 0) {
            printf("  [pylist_index] Found at index %d (lnode@%p)\n", idx, (void*)cur);
            return idx;
        }
        cur = cur->next;
        idx++;
    }
    printf("  [pylist_index] Not found\n");
    return -1;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);  /* Internal */

    struct pylist * lst = pylist_new();
    pylist_append(lst, "Hello world");
    pylist_print(lst);
    pylist_append(lst, "Catch phrase");
    pylist_print(lst);
    pylist_append(lst, "Brian");
    pylist_print(lst);
    printf("Length = %d\n", pylist_len(lst));
    printf("Brian? %d\n", pylist_index(lst, "Brian"));
    printf("Bob? %d\n", pylist_index(lst, "Bob"));
    pylist_del(lst);
    return 0;
}

/*
Tutorial Notes:
- This struct and functions mimic a subset of Python's list class in C.
- The list is singly linked, with head/tail pointers and a count.
- All memory is managed with malloc/free.
- This is a foundation for more advanced list types in C.
*/
