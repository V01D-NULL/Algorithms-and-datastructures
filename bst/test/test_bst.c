#include "../bst.h"
#include <stdio.h>
#include <stdlib.h>

void print_delete_print(BstNode *tree, BstData data);

int main(void)
{
    printf("Inserting a bunch of nodes\n");
    BstNode *tree = bst_create(3);
    bst_insert(tree, 5);
    bst_insert(tree, 1);
    bst_insert(tree, 7);

    print_delete_print(tree, 5);

    BstNode *node = bst_search(tree, 5);
    if (node != NULL)
        printf("Found node 5: (Address: %p, Data: %d)\n", node, node->data);
    else
        printf("Could not find node 5\n");

    bst_destroy(tree);

    return 0;
}

void print_delete_print(BstNode *tree, BstData data)
{
    printf("\n-- Printing tree structure before deletion --");
    bst_print(tree);

    printf("\n -- Deleting node '%d' --\n", data);
    bst_delete(tree, data);

    printf("\n-- Printing tree structure after deletion --");
    bst_print(tree);
}