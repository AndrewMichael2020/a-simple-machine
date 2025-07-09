/*
 * binary_tree_wordcount.c
 *
 * Andrew M's Tutorial: Word Frequency Count with a Binary Tree in C
 *
 * This program demonstrates how to use a binary search tree (BST) to count
 * the occurrences of words in input. Each node contains a word, a count,
 * and pointers to left and right children. The tree is printed in order.
 *
 * Author: Andrew M.
 * Date: July 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

// Tree node structure
struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

typedef struct tnode TNode;

// Create a new tree node, with debug print
TNode *talloc(const char *w) {
    TNode *node = (TNode *)malloc(sizeof(TNode));
    if (!node) {
        fprintf(stderr, "[Error] Memory allocation failed for node with word '%s'\n", w);
        return NULL;
    }
    node->word = strdup(w);
    node->count = 1;
    node->left = node->right = NULL;
    printf("[Alloc] New node at %p for word '%s'\n", (void*)node, w);
    return node;
}

// Insert or update a word in the tree, with debug prints
TNode *tree(TNode *p, const char *w) {
    int cond;
    if (p == NULL) {
        printf("[Insert] '%s' (new leaf)\n", w);
        return talloc(w);
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
        printf("[Update] '%s' already exists at %p, increment count to %d\n", w, (void*)p, p->count);
    } else if (cond < 0) {
        printf("[Traverse] '%s' < '%s', go left from %p\n", w, p->word, (void*)p);
        p->left = tree(p->left, w);
    } else {
        printf("[Traverse] '%s' > '%s', go right from %p\n", w, p->word, (void*)p);
        p->right = tree(p->right, w);
    }
    return p;
}

// Print the tree in-order, with debug prints
void treeprint(const TNode *p) {
    if (p != NULL) {
        printf("[treeprint] At node %p (word='%s', count=%d)\n", (void*)p, p->word, p->count);
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

// Free the tree, with debug prints
void treefree(TNode *p) {
    if (p) {
        printf("[Free] Freeing node at %p (word='%s')\n", (void*)p, p->word);
        treefree(p->left);
        treefree(p->right);
        free(p->word);
        free(p);
    }
}

// Get next word from input (letters only, lowercased)
int getword(char *word, int lim) {
    int c;
    char *w = word;
    // Skip whitespace
    while (isspace(c = getchar()))
        ;
    if (c == EOF)
        return EOF;
    if (!isalpha(c)) {
        *w++ = c;
        *w = '\0';
        return c;
    }
    *w++ = tolower(c);
    while (--lim > 0) {
        c = getchar();
        if (!isalnum(c)) {
            ungetc(c, stdin);
            break;
        }
        *w++ = tolower(c);
    }
    *w = '\0';
    return 'a'; // LETTER
}

void run_demo() {
    printf("Andrew M's Binary Tree Word Count Tutorial\n");
    printf("------------------------------------------\n");
    printf("Enter words (Ctrl+D to end):\n");
    TNode *root = NULL;
    char word[MAXWORD];
    int t;
    while ((t = getword(word, MAXWORD)) != EOF) {
        if (isalpha(word[0]))
            root = tree(root, word);
    }
    printf("\nWord frequencies (in order):\n");
    treeprint(root);
    treefree(root);
}

int main() {
    run_demo();
    return 0;
}

/*
Tutorial Notes:
- Each node contains a word, count, and left/right children.
- Words are inserted in order; duplicates increment the count.
- The tree is printed in sorted order (in-order traversal).
- This is a classic recursive data structure in C.
*/
