#include "../queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* Create queue */
    Queue *q = new_queue();

    /* Enqueue 123 and 456 */
    printf("Enqueueing '123' and '456'\n");
    QueueItem *a = new_item(123);
    QueueItem *b = new_item(456);
    enqueue(q, a);
    enqueue(q, b);
    print_items(q);

    /* Dequeue an item */
    printf("Dequeueing '123'\n");
    QueueItem *dequeued_item = dequeue(q);
    printf("Dequeued item has data: %d\n", dequeued_item->data);
    print_items(q);

    /* Dequeue another item */
    printf("Dequeueing '456'\n");
    QueueItem *dequeued_item2 = dequeue(q);
    printf("Dequeued item has data: %d\n", dequeued_item2->data);
    print_items(q);

    /* Try to dequeue an item from an empty queue. This will fail an assertion */
    // dequeue(q);

    /* Free items stored in the queue */
    delete_queue(q);

    /* Manually free dequeued items and the queue itself */
    free(a);
    free(b);
    free(q);

    return 0;
}