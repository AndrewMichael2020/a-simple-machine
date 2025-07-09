/*
 * point_oop_demo.c
 *
 * Andrew M's Tutorial: Simulating OOP in C with Structs and Function Pointers
 *
 * This program demonstrates how to implement object-oriented programming (OOP) concepts
 * in C using structs and function pointers, similar to Python classes and methods.
 *
 * Author: Andrew M.
 * Date: July 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Struct Point: Represents a 2D point with OOP-like methods.
 * Members:
 *   - x, y: coordinates
 *   - del: destructor (frees memory)
 *   - dump: prints the point
 *   - origin: computes distance from origin
 *
 * This is similar to a Python class with methods:
 *   class Point:
 *       def __init__(self, x, y): ...
 *       def dump(self): ...
 *       def origin(self): ...
 *       def __del__(self): ...
 */
struct Point {
    double x;
    double y;
    void (*del)(const struct Point* self);
    void (*dump)(const struct Point* self);
    double (*origin)(const struct Point* self);
};

typedef struct Point Point;

/**
 * Prints the point's address and coordinates.
 */
void point_dump(const Point* self) {
    printf("[Dump] Object Point@%p\n", (void*)self);
    printf("       |-- x = %.6f\n", self->x);
    printf("       |-- y = %.6f\n", self->y);
    printf("       |-- dump ptr = %p\n", (void*)self->dump);
    printf("       |-- origin ptr = %p\n", (void*)self->origin);
    printf("       |-- del ptr = %p\n", (void*)self->del);
}

/**
 * Frees the memory for the point.
 */
void point_del(const Point* self) {
    printf("[Delete] Freeing Point@%p\n", (void*)self);
    printf("         |-- x = %.6f\n", self->x);
    printf("         |-- y = %.6f\n", self->y);
    printf("         |-- (struct size: %zu bytes)\n", sizeof(Point));
    free((void*)self);
}

/**
 * Returns the distance from the origin (0,0).
 */
double point_origin(const Point* self) {
    double dist = sqrt(self->x * self->x + self->y * self->y);
    printf("[Origin] Called for Point@%p\n", (void*)self);
    printf("         |-- x = %.6f\n", self->x);
    printf("         |-- y = %.6f\n", self->y);
    printf("         |-- sqrt(x^2 + y^2) = %.6f\n", dist);
    return dist;
}

/**
 * Allocates and initializes a new Point object.
 * Returns: pointer to new Point
 */
Point* point_new(double x, double y) {
    printf("[New] Allocating Point with x=%.6f, y=%.6f\n", x, y);
    Point* p = (Point*)malloc(sizeof(Point));
    if (!p) {
        fprintf(stderr, "[Error] Memory allocation failed for Point\n");
        exit(EXIT_FAILURE);
    }
    printf("[New] malloc returned address %p (%zu bytes)\n", (void*)p, sizeof(Point));
    p->x = x;
    p->y = y;
    p->dump = point_dump;
    p->origin = point_origin;
    p->del = point_del;
    printf("[New] Point@%p created and initialized\n", (void*)p);
    return p;
}

void run_demo() {
    printf("Andrew M's OOP-in-C Point Tutorial\n");
    printf("-----------------------------------\n");
    printf("Simulating Python-like classes and methods in C using structs and function pointers.\n\n");

    Point* pt = point_new(4.0, 5.0);
    printf("\nCalling pt->dump(pt):\n");
    pt->dump(pt);
    printf("\nCalling pt->origin(pt):\n");
    double dist = pt->origin(pt);
    printf("[Result] Origin distance: %.6f\n", dist);
    printf("\nCalling pt->del(pt):\n");
    pt->del(pt);
}

int main(void) {
    run_demo();
    return 0;
}

/*
Tutorial Notes:
- This pattern simulates OOP in C, similar to Python classes with methods.
- Each struct instance has function pointers for its "methods".
- Methods are called as pt->method(pt), like pt.method() in Python.
- This is a powerful C idiom for encapsulation and polymorphism.
*/
