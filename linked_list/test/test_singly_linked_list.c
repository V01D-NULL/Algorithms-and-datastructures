#include "../singly_linked_list.h"
#include <stdio.h>

int main(void)
{
    /* Create list */
    List *list = init_head(123);

    /* Append a node */
    printf("Appending node with a value of: 789\n");
    Node *node = new_node(789);
    append_node(list->head, node);

    /* Print nodes 123, 789 */
    print_nodes(list->head);

    printf("\nInserting node with a value of 456 between 123 and 789\n");
    insert_node(list->head, list->head, node, new_node(456));
    print_nodes(list->head);

    /* Remove node 789 */
    printf("\nRemoving node with a value of: %d\n", node->data);
    remove_node(list->head, node);
    print_nodes(list->head);

    return 0;
}