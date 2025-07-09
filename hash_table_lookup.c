/*
 * hash_table_lookup.c
 *
 * Andrew M's Tutorial: Table Lookup with Hash Maps in C
 *
 * This program demonstrates a simple hash table (hash map) for string-to-string mapping,
 * inspired by classic C textbooks. It includes install() and lookup() functions, a simple
 * hash function, and dynamic memory management using malloc/free.
 *
 * Author: Andrew M.
 * Date: July 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 100

struct nlist {
    char *name;
    char *def;
    struct nlist *next;
};

static struct nlist *hashtab[HASHSIZE]; // pointer table

// Hash function: sum of chars mod HASHSIZE
unsigned hash(const char *s) {
    unsigned hashval = 0;
    while (*s)
        hashval += (unsigned char)*s++;
    return hashval % HASHSIZE;
}

// Lookup: find entry by name
struct nlist *lookup(const char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

// Install: add or update (name, def) pair
struct nlist *install(const char *name, const char *def) {
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) {
        // Not found, create new
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL) return NULL;
        np->name = strdup(name);
        if (np->name == NULL) return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        // Already there, replace def
        free(np->def);
    }
    np->def = strdup(def);
    if (np->def == NULL) return NULL;
    return np;
}

// Utility: print the whole table
void print_table() {
    printf("\nCurrent hash table contents:\n");
    for (int i = 0; i < HASHSIZE; ++i) {
        struct nlist *np = hashtab[i];
        if (np) {
            printf("Bucket %d:\n", i);
            while (np) {
                printf("  %s => %s\n", np->name, np->def);
                np = np->next;
            }
        }
    }
}

// Free all memory in the table
void free_table() {
    for (int i = 0; i < HASHSIZE; ++i) {
        struct nlist *np = hashtab[i];
        while (np) {
            struct nlist *next = np->next;
            free(np->name);
            free(np->def);
            free(np);
            np = next;
        }
        hashtab[i] = NULL;
    }
}

void run_demo() {
    printf("Andrew M's Hash Table Lookup Tutorial\n");
    printf("-------------------------------------\n");
    printf("Installing #define-style pairs...\n");
    install("YES", "1");
    install("NO", "0");
    install("PI", "3.14159");
    install("HELLO", "world");
    install("YES", "42"); // update
    print_table();

    printf("\nLooking up some names...\n");
    const char *names[] = {"YES", "NO", "PI", "HELLO", "MISSING"};
    for (int i = 0; i < 5; ++i) {
        struct nlist *np = lookup(names[i]);
        if (np)
            printf("lookup('%s') => '%s'\n", names[i], np->def);
        else
            printf("lookup('%s') => not found\n", names[i]);
    }

    free_table();
}

int main() {
    run_demo();
    return 0;
}

/*
Tutorial Notes:
- Hash tables use an array of pointers to chains (linked lists) for collision resolution.
- The hash function maps a string to a bucket index.
- install() adds or updates entries; lookup() searches for a name.
- This is the core of a symbol table or macro processor in C.
- Modern C uses malloc/free for dynamic memory management.
*/
