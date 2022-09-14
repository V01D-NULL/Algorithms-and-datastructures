#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

/* Index into the children array of __bst_node */
#define BST_LEFT 0
#define BST_RIGHT 1

#define bst_left_node(x) x->children[BST_LEFT]
#define bst_right_node(x) x->children[BST_RIGHT]

typedef int BstData;

typedef struct __bst_node
{
    struct __bst_node *parent;
    struct __bst_node *children[2];
    BstData data;
} BstNode;

BstNode *bst_create(BstData data);
BstNode *bst_search(BstNode *tree, BstData data);
void bst_insert(BstNode *tree, BstData data);
BstNode *bst_delete(BstNode *tree, BstData data);

void bst_print(BstNode *tree);
void bst_destroy(BstNode *tree);

#endif // BINARY_SEARCH_TREE_H
