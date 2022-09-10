#ifndef DEQUE_H
#define DEQUE_H

#include "../vector/vector.h"

typedef struct
{
    Vector *queue;
} Deque;

Deque *new_deque(int capacity);
void deque_push_back(Deque *q, void *data);
void deque_push_front(Deque *q, void *data);
void deque_pop_back(Deque *q);
void deque_pop_front(Deque *q);
void *deque_front(Deque *q);
void *deque_back(Deque *q);
void delete_deque(Deque *q);

#endif // DEQUE_H