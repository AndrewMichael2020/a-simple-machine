/*
 * linked_list_delete.c
 *
 * Andrew M's Tutorial: Deleting an Item from a Singly Linked List in C
 *
 * This program demonstrates how to delete a node from a singly linked list.
 * It covers all three cases: deleting from the middle, the start, and the end of the list.
 *
 * The example is inspired by classic CS diagrams (see README or provided image).
 *
 * Author: Andrew M.
 * Date: July 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for a singly linked list
struct Node {
    char text[16];
    struct Node* next;
};

typedef struct Node Node;

// Utility: Print the linked list
void print_list(Node* head) {
    printf("List: ");
    while (head) {
        printf("[%s] -> ", head->text);
        head = head->next;
    }
    printf("NULL\n");
}

// Utility: Create a new node
Node* create_node(const char* text) {
    Node* node = (Node*)malloc(sizeof(Node));
    strncpy(node->text, text, sizeof(node->text)-1);
    node->text[sizeof(node->text)-1] = '\0';
    node->next = NULL;
    return node;
}

// Delete the first node with matching text
// Returns new head pointer
Node* delete_node(Node* head, const char* target) {
    Node* current = head;
    Node* prev = NULL;
    while (current) {
        if (strcmp(current->text, target) == 0) {
            // Found node to delete
            if (prev == NULL) {
                // Case 2: Deleting head
                printf("Deleting head node: %s\n", current->text);
                head = current->next;
            } else {
                // Case 1 or 3: Middle or end
                printf("Deleting node: %s\n", current->text);
                prev->next = current->next;
            }
            Node* to_free = current;
            current = current->next; // Move to next before freeing
            free(to_free);
            printf("List after deletion: ");
            print_list(head); // Show the list after deletion with a label
            return head;
        }
        prev = current;
        current = current->next;
    }
    printf("Node '%s' not found.\n", target);
    return head;
}

// Build a sample list: "C" -> "is" -> "fun" -> NULL
Node* build_sample_list() {
    Node* n1 = create_node("C");
    Node* n2 = create_node("is");
    Node* n3 = create_node("fun");
    n1->next = n2;
    n2->next = n3;
    return n1;
}

int main() {
    printf("Linked List Deletion Tutorial\n");
    printf("-----------------------------\n");
    printf("We will build a list: C -> is -> fun\n");

    // Case 1: Delete from the middle (delete 'is')
    Node* head1 = build_sample_list();
    printf("\nCase 1: Delete from the middle (delete 'is')\n");
    print_list(head1);
    head1 = delete_node(head1, "is");
    // Free remaining nodes
    while (head1) {
        Node* tmp = head1;
        head1 = head1->next;
        free(tmp);
    }

    // Case 2: Delete from the start (delete 'C')
    Node* head2 = build_sample_list();
    printf("\nCase 2: Delete from the start (delete 'C')\n");
    print_list(head2);
    head2 = delete_node(head2, "C");
    while (head2) {
        Node* tmp = head2;
        head2 = head2->next;
        free(tmp);
    }

    // Case 3: Delete from the end (delete 'fun')
    Node* head3 = build_sample_list();
    printf("\nCase 3: Delete from the end (delete 'fun')\n");
    print_list(head3);
    head3 = delete_node(head3, "fun");
    while (head3) {
        Node* tmp = head3;
        head3 = head3->next;
        free(tmp);
    }

    // Try deleting a non-existent node
    Node* head4 = build_sample_list();
    printf("\nTry deleting a non-existent node ('nope')\n");
    print_list(head4);
    head4 = delete_node(head4, "nope");
    while (head4) {
        Node* tmp = head4;
        head4 = head4->next;
        free(tmp);
    }

    return 0;
}

/*
Tutorial Notes:
- To delete a node, scan the list to find the node and keep track of the previous node.
- If deleting the head, update the head pointer.
- If deleting from the middle or end, set prev->next = current->next.
- Always free the deleted node's memory.
- Drawing diagrams helps avoid pointer mistakes!
*/
