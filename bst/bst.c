#include "displayTree.h"
#include "bst.h"

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

BstNode *bst_create(BstData data)
{
    BstNode *n = malloc(sizeof(BstNode));
    n->data = data;
    return n;
}

BstNode *bst_search(BstNode *tree, BstData data)
{

    if (!tree)
        return NULL;

    if (data == tree->data)
        return tree;

    int child = data < tree->data ? BST_LEFT : BST_RIGHT;
    return bst_search(tree->children[child], data);
}

void bst_insert(BstNode *tree, BstData data)
{
    assert(tree != NULL && "Tree cannot be NULL");
    BstNode *root = tree;
    BstNode *new_node = NULL;

    while (tree != NULL)
    {
        BstNode *parent = tree;
        if (data == tree->data)
            return;

        int child = data < tree->data ? BST_LEFT : BST_RIGHT;
        if (!tree->children[child])
        {
            tree->children[child] = new_node = bst_create(data);
            break;
        }
        tree = tree->children[child];
    }
}

BstNode *__bst_inorder_successor(BstNode *node)
{
    for (; node && bst_left_node(node);)
        node = bst_left_node(node);

    return node;
}

bool __bst_has_two_children(BstNode *node)
{
    return (bst_left_node(node) && bst_right_node(node));
}

BstNode *__bst_delete_helper(BstNode *root, BstData data)
{
    if (root == NULL)
        return root;

    // Traverse to the right or left subtree
    if (data != root->data)
    {
        int direction = data < root->data ? BST_LEFT : BST_RIGHT;
        root->children[direction] = __bst_delete_helper(root->children[direction], data);
    }
    else
    {
        if (!__bst_has_two_children(root))
        {
            BstNode *child = root->children[root->data < data ? BST_LEFT : BST_RIGHT];
            free(root);
            return child;
        }

        BstNode *successor = __bst_inorder_successor(bst_right_node(root));
        root->data = successor->data;
        root->children[BST_RIGHT] = __bst_delete_helper(root->children[BST_RIGHT], successor->data);
    }
    return root;
}

BstNode *bst_delete(BstNode *root, BstData data)
{
    BstNode *node = NULL;

    if ((node = bst_search(root, data)) == NULL)
    {
        printf("Unable to find node '%d'\n", data);
        return root;
    }

    __bst_delete_helper(root, data);
    return root;
}

void bst_print(BstNode *tree)
{
    draw(tree);
}

void bst_destroy(BstNode *tree)
{
    if (!tree)
        return;

    bst_destroy(tree->children[BST_LEFT]);
    bst_destroy(tree->children[BST_RIGHT]);

    free(tree);
}