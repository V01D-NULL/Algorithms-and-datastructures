#ifndef QUEUE_H
#define QUEUE_H

typedef struct __queue_item
{
    struct __queue_item *next, *prev;
    int data;
} QueueItem;

typedef struct
{
    QueueItem *head, *tail;
    int elements;
} Queue;

QueueItem *new_item(int data);
Queue *new_queue(void);
void delete_queue(Queue *q);
void enqueue(Queue *q, QueueItem *item);
QueueItem *dequeue(Queue *q);

void print_items(Queue *q);

#endif // QUEUE_H