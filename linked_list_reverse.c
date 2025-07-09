/*
 * linked_list_reverse.c
 *
 * Andrew M's Tutorial: Reversing a Doubly Linked List in C
 *
 * This program demonstrates how to reverse a doubly linked list in place.
 * It shows the list before and after reversal, with clear output and comments.
 *
 * Author: Andrew M.
 * Date: July 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for a doubly linked list
struct Node {
    char text[16];
    struct Node* next;
    struct Node* prev;
};

typedef struct Node Node;

// Utility: Print the doubly linked list (forward)
void print_list(Node* head) {
    printf("List (forward): ");
    while (head) {
        printf("[%s] <-> ", head->text);
        head = head->next;
    }
    printf("NULL\n");
}

// Utility: Print the doubly linked list (backward)
void print_list_reverse(Node* tail) {
    printf("List (backward): ");
    while (tail) {
        printf("[%s] <-> ", tail->text);
        tail = tail->prev;
    }
    printf("NULL\n");
}

/**
 * Utility: Create a new node
 * Allocates and initializes a new Node with the given text.
 */
Node* create_node(const char* text) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strncpy(node->text, text, sizeof(node->text) - 1);
    node->text[sizeof(node->text) - 1] = '\0';
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// Reverse the doubly linked list in place, with debug prints
Node* reverse_list(Node* head) {
    Node* current = head;
    Node* temp = NULL;
    int step = 0;
    printf("\n[Debug] Starting reversal...\n");
    while (current) {
        printf("[Debug] Step %d: At node '%s'\n", step, current->text);
        printf("         Before swap: prev=%s, next=%s\n",
            current->prev ? current->prev->text : "NULL",
            current->next ? current->next->text : "NULL");
        // Swap next and prev
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        printf("         After swap:  prev=%s, next=%s\n",
            current->prev ? current->prev->text : "NULL",
            current->next ? current->next->text : "NULL");
        // Move to next node (which is previous before swap)
        current = current->prev;
        step++;
    }
    // After the loop, temp points to the old head's prev, which is the new head
    if (temp) {
        printf("[Debug] New head is '%s'\n", temp->prev ? temp->prev->text : "NULL");
        head = temp->prev;
    }
    printf("[Debug] Reversal complete.\n\n");
    return head;
}

// Build a sample list: "C" <-> "is" <-> "fun" <-> NULL
Node* build_sample_list() {
    Node* n1 = create_node("C");
    Node* n2 = create_node("is");
    Node* n3 = create_node("fun");
    n1->next = n2;
    n2->prev = n1;
    n2->next = n3;
    n3->prev = n2;
    return n1;
}

void run_demo() {
    printf("Doubly Linked List Reverse Tutorial\n");
    printf("-----------------------------\n");
    printf("We will build a list: C <-> is <-> fun\n");
    Node* head = build_sample_list();
    print_list(head);
    // Find tail for reverse printing
    Node* tail = head;
    while (tail && tail->next) tail = tail->next;
    print_list_reverse(tail);

    printf("\nReversing the list...\n");
    head = reverse_list(head);
    print_list(head);
    // Find new tail
    tail = head;
    while (tail && tail->next) tail = tail->next;
    print_list_reverse(tail);

    // Free the list
    while (head) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    run_demo();
    return 0;
}

/*
Tutorial Notes:
- To reverse a doubly linked list, iterate through the list and swap the next and prev pointers for each node.
- Use a current pointer to traverse the list and a temp pointer to assist in swapping.
- After reversal, the temp pointer will indicate the new head of the list.
- Drawing diagrams helps understand pointer manipulation!
*/
