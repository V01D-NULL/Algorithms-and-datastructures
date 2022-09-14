#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdbool.h>

/* Branch prediction optimization */
#define RB_UNLIKELY(x) __builtin_expect(!!(x), 0)

/* Node color */
#define RB_BLACK false
#define RB_RED true

/* Index into the children array of __rb_node */
#define RB_LEFT 0
#define RB_RIGHT 1

/* This should help make the code easier to read */
#define rb_left_node(x) x->children[RB_LEFT]
#define rb_right_node(x) x->children[RB_RIGHT]

#define rb_is_red(x) (x->color == RB_RED)
#define rb_insert(root, data)                                     \
    do                                                            \
    {                                                             \
        extern RedBlackNode *__rb_insert(RedBlackNode *, RbData); \
        root = __rb_insert(root, data);                           \
    } while (0)

#define rb_delete(root, data)                                     \
    do                                                            \
    {                                                             \
                                                                  \
        extern RedBlackNode *__rb_delete(RedBlackNode *, RbData); \
        root = __rb_delete(root, data);                           \
    } while (0)

typedef int RbData;

typedef struct __rb_node
{
    bool color; /* 1 = red, 0 = black */
    struct __rb_node *parent;
    struct __rb_node *children[2];
    RbData data;
} RedBlackNode;

RedBlackNode *rb_create(RbData data);
RedBlackNode *rb_search(RedBlackNode *tree, RbData data);
void rb_destroy(RedBlackNode *tree);

void rb_print(RedBlackNode *tree);

#endif // RED_BLACK_TREE_H