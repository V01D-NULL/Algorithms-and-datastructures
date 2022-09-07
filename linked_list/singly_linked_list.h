#ifndef SLIST_H
#define SLIST_H

typedef struct __node
{
	struct __node *next;
	int data;
} Node;

typedef struct
{
	Node *head;
} List;

Node *new_node(int data);
List *init_head(int data);
void append_node(Node *head, Node *node);
void remove_node(Node *head, Node *node);

/* Insert node 'node' between node 'a' and 'b' */
void insert_node(Node *head, Node *a, Node *b, Node *node);

void print_nodes(Node *head);

#endif // SLIST_H