#include "../hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    /* Create a hashmap with a capacity of 2 */
    Hashmap *map = hashmap_create(2, 4);

    /* Insert three items to the hashmap. The hashmap will grow it's capacity internally */
    hashmap_insert(map, (void *)"ABC", (void *)1234);
    hashmap_insert(map, (void *)"CBA", (void *)5555);
    hashmap_insert(map, (void *)"DEF", (void *)5678);

    /* Remove a key-value pair */
    hashmap_remove(map, (void*)"ABC");
    
    /* Try to retrieve a non-existant key-value pair */
    KeyValuePair kvp = hashmap_search(map, (void*)"ABC");
    printf("\nKey-value pair:\n");
    printf("Key  : %s\n", (char*)kvp.key);
    printf("Value: %ld\n", (uint64_t)kvp.value);
    printf("==================\n");	

    /* Insert duplicate keys. This will fail */
    hashmap_insert(map, (void *)"BAR", (void *)"Hi");
    hashmap_insert(map, (void *)"BAR", (void *)"Hi");

    /* Retrieve an existing key-value pair */
    kvp = hashmap_search(map, (void*)"CBA");
    printf("\nKey-value pair:\n");
    printf("Key  : %s\n", (char*)kvp.key);
    printf("Value: %ld\n", (uint64_t)kvp.value);
    printf("==================\n");

    hashmap_destroy(map);
    return 0;
}