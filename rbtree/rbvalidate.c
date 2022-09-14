#include "rbtree.h"
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

/* RB_LEFT or RB_RIGHT */
typedef int RbDirection;

 void __rb_rotate(RedBlackNode *node, RbDirection direction);
void __rb_replace_node(RedBlackNode *old_node, RedBlackNode *new_node);
RedBlackNode *__rb_get_sibling(RedBlackNode *node);

void __rb_rebalance_after_insertion(RedBlackNode *node)
{
    /* Ignore the root and black colored nodes & parents */
    if (!node || !node->parent || (node->color != RB_RED || node->parent->color != RB_RED))
        return;

    /* Store references to some relevant nodes */
    RedBlackNode *grandparent = node->parent->parent;
    RedBlackNode *parent = node->parent;
    RedBlackNode *uncle = __rb_get_sibling(parent);

    if (!grandparent)
    {
        parent->color = RB_BLACK;
        return;
    }

    /* Red parent and uncle (parent is known to be red because it passed the first if statement) */
    if (uncle && rb_is_red(uncle))
    {
        parent->color = uncle->color = RB_BLACK;
        grandparent->color = RB_RED;
        __rb_rebalance_after_insertion(grandparent);
    }

    /* Red parent, black uncle. */
    else
    {
        RbDirection node_rotation = parent->data > node->data ? RB_LEFT : RB_RIGHT;
        RbDirection parent_rotation = grandparent->data > parent->data ? RB_LEFT : RB_RIGHT;

        printf("Performing a %s %s rotation\n", node_rotation ? "right" : "left", parent_rotation ? "right" : "left");

        node->color = RB_BLACK;
        if (node == parent->children[!parent_rotation])
        {
            __rb_rotate(parent, parent_rotation);
            parent = node;
        }

        __rb_rotate(grandparent, node_rotation);

        parent->color = RB_BLACK;
        grandparent->color = RB_RED;
    }
}

/*
    Rotate the red-black tree towards 'direction'.
    Where 'direction' is either RB_RIGHT or RB_LEFT.

    Recommended readings:
        - https://en.wikipedia.org/wiki/Tree_rotation
        - https://strncat.github.io/jekyll/update/2019/05/02/binary-tree-rotation.html
        - https://www.youtube.com/watch?v=HZ9aA3o3FkM (😜)
*/
 void __rb_rotate(RedBlackNode *node, RbDirection direction)
{
    printf("Rotating node '%d' to the %s\n", node->data, direction == RB_RIGHT ? "right" : "left");

    RbDirection inverse_direction = !direction; // right becomes left, left becomes right.
                                                // This helps ensure the structure of the bst stays valid
    printf("node: %d | dir: %d | invdir: %d\n", node->data, direction, inverse_direction);

    RedBlackNode *parent = node->parent;
    RedBlackNode *child = node->children[inverse_direction];

    /* Replace the parent's child if possible */
    __rb_replace_node(node, child);

    node->children[inverse_direction] = child->children[direction];
    if (child->children[direction])
        child->children[direction]->parent = node;

    child->children[direction] = node;
    node->parent = child;
}

RedBlackNode *__rb_get_sibling(RedBlackNode *node)
{
    if (RB_UNLIKELY(!node || !node->parent))
        return NULL;

    /* Figure out if this is the left or right child node */
    int child = node->data < node->parent->data ? RB_RIGHT : RB_LEFT;
    return node->parent->children[child];
}

void __rb_replace_node(RedBlackNode *old_node, RedBlackNode *new_node)
{
    if (old_node == rb_left_node(old_node->parent))
        rb_left_node(old_node->parent) = new_node;
    else if (old_node == rb_right_node(old_node->parent))
        rb_right_node(old_node->parent) = new_node;

    if (new_node)
        new_node->parent = old_node->parent;
}

bool __rb_has_two_children(RedBlackNode *node)
{
    return (rb_left_node(node) && rb_right_node(node));
}