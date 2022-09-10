#include "deque.h"
#include <stdlib.h>

Deque *new_deque(int capacity)
{
    Deque *q = malloc(sizeof(Deque));
    q->queue = vec_init(capacity);
    return q;
}

void deque_push_back(Deque *q, void *data)
{
    vec_push_back(q->queue, data);
}

void deque_push_front(Deque *q, void *data)
{
    vec_insert(q->queue, 0, 0, data);
}

void deque_pop_back(Deque *q)
{
    vec_pop_back(q->queue);
}

void deque_pop_front(Deque *q)
{
    vec_remove(q->queue, 0);
}

void *deque_front(Deque *q)
{
    return vec_front(q->queue);
}

void *deque_back(Deque *q)
{
    return vec_back(q->queue);
}

void delete_deque(Deque *q)
{
    vec_deinit(q->queue);
    free(q);
}