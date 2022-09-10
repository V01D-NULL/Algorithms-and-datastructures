#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>
#include "../vector/vector.h"

typedef void *Key;
typedef void *Value;

typedef struct
{
    Key key;
    Value value;
} KeyValuePair;

typedef struct
{
    /* Set of keys and values */
    Vector *keys;
    Vector *values;
    
    int key_size, capacity;
    bool resize;
} Hashmap;

Hashmap *hashmap_create(int capacity, int key_size);
void hashmap_insert(Hashmap *map, Key key, Value value);
KeyValuePair hashmap_search(Hashmap *map, Key key);
void hashmap_remove(Hashmap *map, Key key);
void hashmap_destroy(Hashmap *map);

#endif // HASHMAP_H