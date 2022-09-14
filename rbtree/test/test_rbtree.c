#include "../rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void print_delete_print(RedBlackNode *tree, int data);

int main(void)
{
    /* Test 1: Insert a bunch of nodes and delete some in the middle */
    printf("Test 1: Insert a bunch of nodes and delete some in the middle\n");
    printf("Inserting a bunch of nodes...\n\n");
    RedBlackNode *tree = rb_create(3);
    rb_insert(tree, 5);
    rb_insert(tree, 1);
    rb_insert(tree, 7);
    rb_insert(tree, 6);
    rb_insert(tree, 8);
    print_delete_print(tree, 6);
    rb_destroy(tree);

    /* Test 2: Insert only three nodes (one root, two children) and remove the root */
    printf("\n\nTest 2: Insert only three nodes (one root, two children) and remove the root\n");
    RedBlackNode *tree_2 = rb_create(3);
    rb_insert(tree_2, 2);
    rb_insert(tree_2, 1);
    print_delete_print(tree_2, 3);
    rb_destroy(tree_2);

    return 0;
}

void print_delete_print(RedBlackNode *tree, int data)
{
    printf("\n-- Printing tree structure before deletion --");
    rb_print(tree);

    printf("\n -- Deleting node '%d' --\n", data);
    rb_delete(tree, data);

    printf("\n-- Printing tree structure after deletion --");
    rb_print(tree);
}