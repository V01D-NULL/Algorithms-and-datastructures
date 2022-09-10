#include "../deque.h"
#include <stdio.h>
#include <stdlib.h>

#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"

int main(void)
{
    /* Create a deque */
    Deque *q = new_deque(5);

    /* Push 123, 456 and 789 to the back of the queue */
    printf("Pushing 123, 456 and 789 to the back of the deque\n");
    deque_push_back(q, (void*)123);
    deque_push_back(q, (void*)456);
    deque_push_back(q, (void*)789);

    /* Print all elements in the deque */
    printf("Printing items in deque:\n");
    vec_foreach(q->queue, i)
    {
        printf("q->queue[%d] = %d\n", i, (int)q->queue->data[i]);
    }

    /* Pop the head from the deque */
    printf("\nPopping item from the front of the deque\n");
    deque_pop_front(q);

    /* Print all elements in the deque */
    printf("Printing items in deque:\n");
    vec_foreach(q->queue, i)
    {
        printf("q->queue[%d] = %d\n", i, (int)q->queue->data[i]);
    }

    /* Push 999 to the front of the deque, effectively replacing the current head with '999' */
    printf("\nPushing '999' to the front of the deque\n");
    deque_push_front(q, (void*)999);

    /* Print all elements in the deque */
    printf("Printing items in deque:\n");
    vec_foreach(q->queue, i)
    {
        printf("q->queue[%d] = %d\n", i, (int)q->queue->data[i]);
    }

    /* Retrieve the front and back of the deque */
    printf("Front: %d | back: %d\n", (int)deque_front(q), (int)deque_back(q));

    delete_deque(q);

    return 0;
}