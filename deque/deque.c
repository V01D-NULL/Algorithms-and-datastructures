#include "deque.h"
#include <stdlib.h>

Deque *new_deque(int capacity)
{
    Deque *q = malloc(sizeof(Deque));
    q->queue = vec_init(capacity);
    return q;
}

void deque_push_back(Deque *q, int data)
{
    vec_push_back(q->queue, data);
}

void deque_push_front(Deque *q, int data)
{
    vec_insert(q->queue, 0, 0, data);
}

void deque_pop_back(Deque *q)
{
    vec_pop_back(q->queue);
}

void deque_pop_front(Deque *q)
{
    Vector *v = q->queue;

    for (int i = 0; i < v->elements; i++)
        v->data[i] = v->data[i + 1];
    --v->elements;
}

int deque_front(Deque *q)
{
    return vec_front(q->queue);
}

int deque_back(Deque *q)
{
    return vec_back(q->queue);
}

void delete_deque(Deque *q)
{
    vec_deinit(q->queue);
    free(q);
}