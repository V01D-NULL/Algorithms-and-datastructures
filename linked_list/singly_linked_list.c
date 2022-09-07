#include "singly_linked_list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>

Node *new_node(int data)
{
	Node *n = malloc(sizeof(Node));
	n->next = NULL;
	n->data = data;
	return n;
}

List *init_head(int data)
{
	List *list = malloc(sizeof(List));
	list->head = new_node(data);
	return list;
}

void append_node(Node *head, Node *node)
{
	assert(node->next == NULL && "Cannot append a node with a next pointer. Use insert() instead.");
	while (head->next)
		head = head->next;

	head->next = node;
}

void remove_node(Node *head, Node *node)
{
	while (head->next)
	{
		if (head->next == node)
		{
			head->next = node->next;
			return;
		}
		head = head->next;
	}
}

void insert_node(Node *head, Node *a, Node *b, Node *node)
{
	while (head->next)
	{
		if (head == a)
		{
			node->next = b;
			a->next = node;
			head = node;
			return;
		}
		head = head->next;
	}
}

void print_nodes(Node *head)
{
	while (head)
	{
		printf("%p | %d\n", head, head->data);
		head = head->next;
	}
}
