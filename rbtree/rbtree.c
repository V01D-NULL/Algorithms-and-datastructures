#include "displayTree.h"
#include "rbtree.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

/* rbvalidate.c */
extern RedBlackNode *__rb_rebalance_after_insertion(RedBlackNode *node);
extern RedBlackNode *__rb_get_sibling(RedBlackNode *node);
extern bool __rb_has_two_children(RedBlackNode *node);

RedBlackNode *rb_create_node(RedBlackNode *parent, RbData data, int color)
{
    RedBlackNode *n = malloc(sizeof(RedBlackNode));
    n->data = data;
    n->parent = parent;
    n->children[RB_LEFT] = n->children[RB_RIGHT] = NULL;
    n->color = color;
    return n;
}

RedBlackNode *rb_create(RbData data)
{
    /* Root node */
    return rb_create_node(NULL, data, RB_BLACK);
}

RedBlackNode *rb_search(RedBlackNode *tree, RbData data)
{
    if (RB_UNLIKELY(!tree))
        return NULL;

    if (data == tree->data)
        return tree;

    int child = data < tree->data ? RB_LEFT : RB_RIGHT;
    return rb_search(tree->children[child], data);
}

RedBlackNode *node_to_root(RedBlackNode *new_root)
{
    /* Delete the previous root node */
    free(new_root->parent);
    new_root->parent = NULL;

    new_root->color = RB_BLACK;
    rb_right_node(new_root) = rb_left_node(new_root) = NULL;
    return new_root;
}

RedBlackNode *__rb_insert(RedBlackNode *tree, RbData data)
{
    assert(tree != NULL && "Tree cannot be NULL");
    RedBlackNode *root = tree;
    RedBlackNode *new_node = NULL;

    while (tree != NULL)
    {
        RedBlackNode *parent = tree;
        if (data == tree->data)
            return root;

        int child = data < tree->data ? RB_LEFT : RB_RIGHT;
        if (!tree->children[child])
        {
            tree->children[child] = new_node = rb_create_node(parent, data, RB_RED);
            break;
        }
        tree = tree->children[child];
    }

    /*
        This accounts for a scenario in which a tree has one of the following structures:
        (All left nodes)
            3  (root)
           / \
          2  (nil uncle)
         /
        1 (new_node)

        or this:
        (All right nodes)
                        3  (root)
                       / \
            (nil uncle)   4
                           \
                            5  (new_node)


        This requires the *root* node to be rotated, which __rb_rebalance_after_insertion does not account for.
        __rb_rebalance_after_insertion assumes there is a left and a right node for the root and will fail if that isn't the case.
    */
    if (new_node->parent->parent == root && !__rb_get_sibling(new_node->parent))
    {
        int direction = data < root->data ? RB_LEFT : RB_RIGHT;
        int inverse_direction = !direction;
        RedBlackNode *node = root;
        RedBlackNode *parent = new_node->parent;

        node = node->children[direction]->children[direction];
        parent = node->parent;

        parent->children[inverse_direction] = parent->parent;
        parent->parent->children[direction] = NULL;
        parent->color = RB_BLACK;
        parent->children[RB_LEFT]->color = RB_RED;
        parent->children[RB_RIGHT]->color = RB_RED;
        parent->parent = NULL;

        return parent;
    }
    __rb_rebalance_after_insertion(new_node);
    root->color = RB_BLACK; // Enforce black roots
    return root;
}

RedBlackNode *__rb_inorder_successor(RedBlackNode *node)
{
    for (; node && rb_left_node(node);)
        node = rb_left_node(node);

    return node;
}

RedBlackNode *__rb_delete_helper(RedBlackNode *root, RbData data)
{
    if (!root)
        return NULL;

    // Traverse to the right or left subtree
    if (data != root->data)
    {
        int direction = data < root->data ? RB_LEFT : RB_RIGHT;
        root->children[direction] = __rb_delete_helper(root->children[direction], data);
    }

    else
    {
        if (!__rb_has_two_children(root))
        {
            RedBlackNode *child = root->children[root->data < data ? RB_LEFT : RB_RIGHT];
            free(root);
            return child;
        }

        RedBlackNode *successor = __rb_inorder_successor(rb_right_node(root));
        root->data = successor->data;
        root->children[RB_RIGHT] = __rb_delete_helper(root->children[RB_RIGHT], successor->data);
    }

    return root;
}

RedBlackNode *__rb_delete(RedBlackNode *tree, RbData data)
{
    printf(/* red */ "\033[31m" "NOTE: Deletion has not been fully implemented yet, using it will result in an unbalanced tree\n" /* default */ "\033[0;39m");
    RedBlackNode *node = NULL;

    /* Find node marked for deletion */
    if ((node = rb_search(tree, data)) == NULL)
    {
        printf("Unable to find node '%d'\n", data);
        return tree;
    }

    if (node == tree)
        return node_to_root(node->children[data < node->data ? RB_LEFT : RB_RIGHT]);

    __rb_delete_helper(tree, data);
    return tree;
}

void rb_print(RedBlackNode *tree)
{
    draw(tree);
}

void rb_destroy(RedBlackNode *tree)
{
    if (!tree)
        return;

    rb_destroy(tree->children[RB_LEFT]);
    rb_destroy(tree->children[RB_RIGHT]);

    free(tree);
}
