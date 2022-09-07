#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

QueueItem *new_item(int data)
{
    QueueItem *item = malloc(sizeof(QueueItem));
    item->data = data;
    item->next = NULL;
    return item;
}

Queue *new_queue(void)
{
    Queue *q = malloc(sizeof(Queue));
    q->head = q->tail = NULL;
    return q;
}

void enqueue(Queue *q, QueueItem *item)
{
    ++q->elements;

    // [head] ||||||| [tail]
    // ^ Update head (item will be the new head)
    if (!q->head)
    {
        q->tail = q->head = item;
        q->tail->next = q->head;
        q->tail->prev = q->head;
        return;
    }

    q->head->prev = item;
    item->next = q->head;
    q->head = item;
}

QueueItem *dequeue(Queue *q)
{
    assert(q->elements >= 1 && "Cannot dequeue items from an empty queue");

    --q->elements;
    QueueItem *old_tail = q->tail;

    q->tail->next = NULL;
    q->tail = q->tail->prev;

    old_tail->next = NULL;
    old_tail->prev = NULL;
    return old_tail;
}

void print_items(Queue *q)
{
    QueueItem *head = q->head;
    int counter = q->elements;
    while (counter--)
    {
        printf("%p | %d\n", head, head->data);
        head = head->next;
    }
}

void delete_queue(Queue *q)
{
    QueueItem *head = q->head;
    int counter = q->elements;
    while (counter--)
        free(dequeue(q));
}