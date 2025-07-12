/*
 * map_encapsulation_demo.c
 *
 * Andrew M's Tutorial: Encapsulation and Python-like "dunder" methods in C
 *
 * This program demonstrates encapsulation by refactoring a dictionary-like
 * class in C to use private (dunder) member variables and method pointers,
 * similar to Python's OOP conventions.
 *
 * Author: Andrew M.
 * Date: July 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * struct MapEntry
 *
 * Represents a single key-value pair in the Map. This is analogous to a dictionary entry in Python.
 * - key: dynamically allocated string (char*)
 * - value: integer value
 * - __prev, __next: pointers for doubly-linked list structure (private, dunder-named)
 *
 * Encapsulation: Only the Map struct manages these entries; users never access them directly.
 */
struct MapEntry {
    char *key;      /* public: key string, dynamically allocated */
    int value;      /* public: integer value */
    struct MapEntry *__prev; /* private: previous entry in linked list */
    struct MapEntry *__next; /* private: next entry in linked list */
};

/*
 * struct Map
 *
 * Encapsulated dictionary-like class in C, inspired by Python's dict and OOP conventions.
 *
 * Encapsulation:
 * - All internal members use double underscore (__), following Python's dunder convention for private attributes.
 * - Only the struct and its public API (function pointers) are exposed; internals are hidden from the user.
 *
 * Function pointers:
 * - Each method (put, get, size, dump, del) is a function pointer, bound to the struct instance.
 * - This simulates member functions in C++ or methods in Python: map->put(map, ...) is like map.put(...) in Python.
 * - The first argument (self) is always the struct pointer, just like 'self' in Python or 'this' in C++.
 *
 * Why pointers?
 * - The Map is allocated dynamically (malloc), so it can grow and shrink at runtime.
 * - Function pointers allow us to bind methods to the struct, enabling OOP-like behavior in C.
 * - All memory management (allocation, freeing) is handled internally, just like Python's automatic memory management.
 */
struct Map {
   /* Private attributes (dunder-named) */
   struct MapEntry *__head;   /* pointer to first entry */
   struct MapEntry *__tail;   /* pointer to last entry */
   int __count;               /* number of entries */

   /* Public API: method pointers (simulating member functions) */
   void (*put)(struct Map* self, char *key, int value);   /* add/update key-value */
   int (*get)(struct Map* self, char *key, int def);      /* get value by key, or default */
   int (*size)(struct Map* self);                         /* get number of entries */
   void (*dump)(struct Map* self);                        /* print all entries */
   void (*del)(struct Map* self);                         /* free all memory */
};

/*
 * __Map_del
 * Frees all memory used by the Map and its entries.
 * This is analogous to Python's __del__ destructor or C++'s destructor.
 * Ensures no memory leaks by freeing each key and entry, then the Map itself.
 */
void __Map_del(struct Map* self) {
    struct MapEntry *cur, *next;
    cur = self->__head;
    while(cur) {
        free(cur->key);
        next = cur->__next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

/*
 * __Map_dump
 * Prints all key-value pairs in the Map, showing the current state.
 * This is similar to Python's dict.__repr__ or __str__ methods.
 * Useful for debugging and introspection.
 */
void __Map_dump(struct Map* self)
{
    struct MapEntry *cur;
    printf("Object Map count=%d\n", self->__count);
    for(cur = self->__head; cur != NULL ; cur = cur->__next ) {
         printf("  %s=%d\n", cur->key, cur->value);
    }
}

/*
 * __Map_find
 * Searches for a key in the Map and returns the entry if found, else NULL.
 * Used internally by put/get to locate existing keys.
 * Encapsulated: not exposed to users, only used by Map methods.
 */
struct MapEntry* __Map_find(struct Map* self, char *key)
{
    struct MapEntry *cur;
    if ( self == NULL || key == NULL ) return NULL;
    for(cur = self->__head; cur != NULL ; cur = cur->__next ) {
        if(strcmp(key, cur->key) == 0 ) return cur;
    }
    return NULL;
}

/*
 * __Map_put
 * Adds a new key-value pair to the Map, or updates the value if the key exists.
 * - If the key exists, updates its value (like dict[key] = value in Python).
 * - If not, allocates a new MapEntry and links it into the doubly-linked list.
 * - Uses strdup to copy the key string, ensuring encapsulation and memory safety.
 * - Updates __head, __tail, and __count as needed.
 *
 * This method is bound to the Map struct as a function pointer, so map->put(map, ...) acts like a member function.
 * This is analogous to Python's dict.__setitem__ or C++'s operator[].
 */
void __Map_put(struct Map* self, char *key, int value) {
    struct MapEntry *old, *new;
    char *new_key;
    if ( key == NULL ) return;

    old = __Map_find(self, key);
    if ( old != NULL ) {
        old->value = value;
        return;
    }

    new = malloc(sizeof(*new));

    new_key = strdup(key);

    new->key = new_key;
    new->value = value;
    new->__prev = self->__tail;
    new->__next = NULL;

    if (self->__tail != NULL)
        self->__tail->__next = new;
    else
        self->__head = new;

    self->__tail = new;

    self->__count++;
}

/*
 * __Map_get
 * Retrieves the value for a given key, or returns the default if not found.
 * - Uses __Map_find to locate the entry.
 * - Returns the value if found, else returns 'def'.
 *
 * This method is bound to the Map struct as a function pointer, so map->get(map, ...) acts like a member function.
 * This is analogous to Python's dict.get(key, default) or C++'s map::find.
 */
int __Map_get(struct Map* self, char *key, int def) {
    struct MapEntry *retval = __Map_find(self, key);
    if (retval == NULL) return def;
    return retval->value;

    return def;
}

/*
 * __Map_size
 * Returns the number of key-value pairs in the Map.
 * This is analogous to Python's len(dict) or C++'s map::size().
 */
int __Map_size(struct Map* self) {
    return self->__count;
}

/*
 * Map_new
 * Allocates and initializes a new Map object.
 * - All internal members are set to initial values.
 * - Function pointers are bound to the appropriate methods, simulating member functions.
 * - Returns a pointer to the new Map, which must be freed with map->del(map).
 *
 * This is analogous to Python's __init__ constructor or C++'s new operator.
 */
struct Map* Map_new() {
    struct Map *map = malloc(sizeof(*map));

    map->__head = NULL;
    map->__tail = NULL;
    map->__count = 0;

    map->put  = &__Map_put;
    map->get  = &__Map_get;
    map->size = &__Map_size;
    map->dump = &__Map_dump;
    map->del  = &__Map_del;

    return map;
}

int main(void)
{
    struct Map * map = Map_new();
    struct MapEntry *cur;

    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Map test\n");
    map->put(map, "z", 8);
    map->put(map, "z", 1);
    map->put(map, "y", 2);
    map->put(map, "b", 3);
    map->put(map, "a", 4);
    map->dump(map);

    printf("size=%d\n", map->size(map));

    printf("z=%d\n", map->get(map, "z", 42));
    printf("x=%d\n", map->get(map, "x", 42));

    map->del(map);
}

/*
Tutorial Notes:
- All "private" members and methods use double underscore (__), following Python convention.
- Methods are stored as function pointers in the struct, simulating Python's bound methods.
- Encapsulation is achieved by only exposing the struct and its public API.
- This is a foundation for more advanced OOP and encapsulation in C.
*/
