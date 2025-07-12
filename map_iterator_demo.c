/*
 * map_iterator_demo.c
 *
 * Andrew M's Tutorial: Iteration and Python-like Map Iterator in C
 *
 * This program extends the encapsulated Map class to support iteration,
 * similar to Python's dict.items(), dict.values(), or C++ STL iterators.
 *
 * Iterators in Python and C++:
 * - In Python, you can iterate over a dict with 'for k, v in d.items()'.
 * - In C++, you use iterators to traverse containers: 'for (auto it = m.begin(); it != m.end(); ++it)'.
 * - In C, we use a struct (MapIter) with a pointer to the current entry and a 'next' method to advance.
 *
 * Why pointers?
 * - Pointers allow us to reference and traverse linked structures (like our doubly-linked list of MapEntry).
 * - The '->' operator in C is used to access members of a struct via a pointer. For example, 'iter->next' means 'the next method of the struct pointed to by iter'.
 * - Each assignment like 'iter->__current = self->__head' sets the iterator to the first entry in the map.
 * - Advancing with 'self->__current = self->__current->__next' moves the iterator to the next entry, just like incrementing an iterator in C++ or moving to the next item in Python.
 *
 * This design allows us to write code like:
 *   iter = map->iter(map);
 *   while ((entry = iter->next(iter)) != NULL) { ... }
 * which closely resembles iteration in higher-level languages.
 *
 * The use of pointers and the '->' operator is essential for dynamic data structures and method binding in C.
 *
 * Author: Andrew M.
 * Date: July 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MapEntry {
    char *key;  /* public: pointer to dynamically allocated string holding the key */
    int value;  /* public: integer value associated with the key */
    struct MapEntry *__prev; // pointer to previous entry in the doubly-linked list
    struct MapEntry *__next; // pointer to next entry in the doubly-linked list
};

/*
 * struct MapIter
 *
 * Iterator for the Map class. Allows sequential access to all entries.
 * - __current: pointer to the current entry in the iteration
 * - next: function pointer to advance and return the next entry
 * - del: function pointer to free the iterator
 *
 * The iterator pattern here mimics Python's iterator protocol and C++ STL iterators.
 * In Python, 'next()' advances the iterator; in C++ '++it' does the same.
 * In C, we use a function pointer 'next' and a struct pointer 'self'.
 *
 * The '->' operator is used to access struct members via a pointer:
 *   iter->next(iter) calls the 'next' method of the iterator struct.
 *   iter->__current accesses the current MapEntry pointer.
 */
struct MapIter {
   struct MapEntry *__current; // pointer to the current entry being iterated over

   struct MapEntry* (*next)(struct MapIter* self); // function pointer to next() method
   void (*del)(struct MapIter* self); // function pointer to del() method
};

struct Map {
   /* Attributes */
   struct MapEntry *__head;
   struct MapEntry *__tail;
   int __count;

   /* Methods */
   void (*put)(struct Map* self, char *key, int value);
   int (*get)(struct Map* self, char *key, int def);
   int (*size)(struct Map* self);
   void (*dump)(struct Map* self);
   struct MapIter* (*iter)(struct Map* self);
   void (*del)(struct Map* self);
};

void __Map_del(struct Map* self) {
    struct MapEntry *cur, *next;
    cur = self->__head;
    while(cur) {
        free(cur->key);
        /* value is just part of the struct */
        next = cur->__next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

void __MapIter_del(struct MapIter* self) {
    // Frees the iterator struct itself. No need to free entries; they belong to the Map.
    free((void *)self);
}

void __Map_dump(struct Map* self)
{
    struct MapEntry *cur;
    // Start at the head of the list and print each entry
    printf("Object Map count=%d\n", self->__count);
    for(cur = self->__head; cur != NULL ; cur = cur->__next ) {
         // cur->key accesses the key string of the current entry
         // cur->value accesses the value of the current entry
         printf("  %s=%d\n", cur->key, cur->value);
    }
}

struct MapEntry* __Map_find(struct Map* self, char *key)
{
    struct MapEntry *cur;
    // Traverse the list to find an entry with the matching key
    if ( self == NULL || key == NULL ) return NULL;
    for(cur = self->__head; cur != NULL ; cur = cur->__next ) {
        // strcmp compares the key strings
        if(strcmp(key, cur->key) == 0 ) return cur;
    }
    return NULL;
}

int __Map_get(struct Map* self, char *key, int def)
{
    // Returns the value for the key, or def if not found
    struct MapEntry *retval = __Map_find(self, key);
    if ( retval == NULL ) return def;
    return retval->value;
}

int __Map_size(struct Map* self)
{
    // Returns the number of entries in the map
    return self->__count;
}

/* --- Student code starts here --- */

/*
 * __Map_put
 * Adds a new key-value pair to the Map, or updates the value if the key exists.
 * - If the key exists, updates its value.
 * - Otherwise, allocates a new MapEntry and links it to the tail.
 */
void __Map_put(struct Map* self, char *key, int value) {
    struct MapEntry *old, *new;
    char *new_key;
    if (key == NULL) return;

    old = __Map_find(self, key); // Find if key already exists
    if (old != NULL) {
        old->value = value; // Update value if key exists
        return;
    }

    new = malloc(sizeof(*new)); // Allocate new entry
    new_key = strdup(key);      // Duplicate key string
    new->key = new_key;         // Set key pointer
    new->value = value;         // Set value
    new->__prev = self->__tail; // Link to previous tail
    new->__next = NULL;         // No next entry yet

    if (self->__tail != NULL)
        self->__tail->__next = new; // Link previous tail to new entry
    else
        self->__head = new;         // If list was empty, set head to new entry

    self->__tail = new;             // Update tail to new entry
    self->__count++;
}

/*
 * __MapIter_next
 * Advances the iterator and returns the next entry, or NULL if done.
 * - Returns the current entry, then advances to the next.
 * - This is similar to Python's 'next()' or C++'s '++it'.
 * - The 'self->__current' pointer keeps track of where we are in the list.
 * - 'self->__current = self->__current->__next' moves to the next entry.
 * - Returning NULL signals the end of iteration, just like StopIteration in Python.
 */
struct MapEntry* __MapIter_next(struct MapIter* self) {
    // Returns the current entry, then advances iterator to next
    if (self->__current == NULL)
        return NULL; // End of iteration

    struct MapEntry *ret = self->__current; // Save current entry
    self->__current = self->__current->__next; // Advance to next entry
    return ret;
}

/*
 * __Map_iter
 * Creates a new iterator for the Map, starting at the head.
 * - Allocates a MapIter struct and sets its __current pointer to the first entry.
 * - Sets the function pointers for next and del methods.
 * - This allows us to traverse the map in order, just like Python's dict or C++'s map.
 */
struct MapIter* __Map_iter(struct Map* self) {
    // Creates a new iterator starting at the head of the map
    struct MapIter *iter = malloc(sizeof(*iter));
    iter->__current = self->__head; // Set current to first entry
    iter->next = &__MapIter_next;   // Set next method
    iter->del = &__MapIter_del;     // Set del method
    return iter;
}

/*
 * Map_new
 * Allocates and initializes a new Map object, including the iterator method.
 */
struct Map * Map_new() {
    struct Map *p = malloc(sizeof(*p));

    p->__head = NULL; // Start with empty list
    p->__tail = NULL;
    p->__count = 0;
    p->put = &__Map_put;   // Bind put method
    p->get = &__Map_get;   // Bind get method
    p->size = &__Map_size; // Bind size method
    p->dump = &__Map_dump; // Bind dump method
    p->iter = &__Map_iter; // Bind iter method
    p->del = &__Map_del;   // Bind del method

    return p;
}

int main(void)
{
    struct Map * map = Map_new(); // Create new map
    struct MapEntry *cur;
    struct MapIter *iter;

    setvbuf(stdout, NULL, _IONBF, 0); // Unbuffered output for debugging

    printf("Map test\n");
    map->put(map, "z", 8); // Add key-value pairs
    map->put(map, "z", 1); // Update value for key "z"
    map->put(map, "y", 2);
    map->put(map, "b", 3);
    map->put(map, "a", 4);
    map->dump(map); // Print all entries

    printf("size=%d\n", map->size(map)); // Print size

    printf("z=%d\n", map->get(map, "z", 42)); // Get value for "z"
    printf("x=%d\n", map->get(map, "x", 42)); // Get value for "x" (not present)

    printf("\nIterate\n");
    iter = map->iter(map); // Create iterator
    while(1) {
        cur = iter->next(iter); // Get next entry
        if ( cur == NULL ) break; // Stop when done
        printf("%s=%d\n", cur->key, cur->value); // Print key-value
    }
    iter->del(iter); // Free iterator

    map->del(map); // Free map and all entries
}
