#include "hashmap.h"
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef VERBOSE
#define printf(...) printf(__VA_ARGS__)
#else
#define printf(...)
#endif

#define __hashmap_compute_index(key, bytes, cap) hash_code_to_index(hash(key, bytes), cap);
#define __hashmap_ensure_unique_key(given_key, found_key, n)                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!found_key)                                                                                                \
            break;                                                                                                     \
                                                                                                                       \
        if (memcmp(given_key, found_key, n) == 0)                                                                      \
        {                                                                                                              \
            printf("A duplicate key was given to the hashmap: %p (%s)\nIgnoring..\n\n", given_key, (char *)given_key); \
            return;                                                                                                    \
        }                                                                                                              \
    } while (0)

static void hashmap_resize(Hashmap *map, int new_capacity);

// Fowler-no-vol hash
static uint64_t hash(const signed char volatile *key, int key_size)
{
    uint64_t hash = 0xcbf29ce484222325;

    for (int i = 0; i < key_size; i++)
    {
        hash ^= key[i];
        hash *= 0x100000001b3;
    }

    return hash;
}

static uint64_t hash_code_to_index(uint64_t hash_code, uint64_t capacity)
{
    return hash_code % capacity;
}

Hashmap *hashmap_create(int capacity, int key_size)
{
    Hashmap *map = malloc(sizeof(Hashmap));
    map->keys = vec_init(capacity);
    map->values = vec_init(capacity);
    map->key_size = key_size;
    map->capacity = capacity;
    map->resize = true;
}

/*
 * Place a key value pair in the hashmap
 *
 *  Parameters:
 *    - key: Unique key
 *    - value: value
 *    - bytes: Length of the key in bytes
 */
void hashmap_insert(Hashmap *map, Key key, Value value)
{
    int index = __hashmap_compute_index((const signed char volatile *)key, map->key_size, map->capacity);
    printf("Projected index of key '%s': %d\n", (char *)key, index);

    if (index >= map->capacity - 1 && map->resize)
        hashmap_resize(map, map->capacity * 2);

    /* Can this item be inserted at 'index'? */
    Key stored_key = vec_get(map->keys, index);
    if (stored_key == NULL)
    {
        __hashmap_ensure_unique_key(key, stored_key, map->key_size);
        goto end;
    }

    /* No, find the next free index */
    vec_foreach(map->keys, i)
    {
        stored_key = vec_get(map->keys, i);
        if (stored_key)
        {
            __hashmap_ensure_unique_key(key, stored_key, map->key_size);
            continue;
        }

        index = i;
        break;
    }

end:
    vec_emplace(map->keys, index, key);
    vec_emplace(map->values, index, value);
    printf("Settled for index '%d'\n\n", index);
}

KeyValuePair hashmap_search(Hashmap *map, Key key)
{
    int index = __hashmap_compute_index(key, map->key_size, map->capacity);

    /* Can we get O(1) with this key? */
    Key stored_key = vec_get(map->keys, index);
    if (stored_key && !memcmp(stored_key, key, map->key_size))
    {
        return (KeyValuePair){
            .key = stored_key,
            .value = vec_get(map->values, index)};
    }

    /* No, find it using linear search */
    vec_foreach(map->keys, i)
    {
        stored_key = vec_get(map->keys, i);
        printf("%d [%d] > %p\n", i, map->capacity, stored_key);

        if (!stored_key || memcmp(stored_key, key, map->key_size) != 0)
            continue;

        return (KeyValuePair){
            .key = stored_key,
            .value = vec_get(map->values, i)};
    }

    return (KeyValuePair){};
}

void hashmap_remove(Hashmap *map, Key key)
{
    int index = __hashmap_compute_index(key, map->key_size, map->capacity);
    int key_value_pairs = map->keys->elements;

    /* Can we get O(1) with this key? */
    if (index >= map->capacity - 1)
        goto no_constant_lookup;

    Key stored_key = vec_get(map->keys, index);
    if (stored_key && !memcmp(stored_key, key, map->key_size))
    {
        vec_emplace(map->keys, index, NULL);
        vec_emplace(map->values, index, NULL);
        return;
    }

    /* No, find it using linear search */
no_constant_lookup:
    vec_foreach(map->keys, i)
    {
        stored_key = vec_get(map->keys, i);
        printf("%d: %p\n", i, stored_key);

        if (!stored_key || memcmp(stored_key, key, map->key_size) != 0)
            continue;

        vec_emplace(map->keys, i, NULL);
        vec_emplace(map->values, i, NULL);
        return;
    }
}

static void hashmap_resize(Hashmap *map, int new_capacity)
{
    assert(new_capacity > 0 && "Cannot resize hashmap to zero elements. Consider destroying it instead");
    assert(map->keys->elements <= new_capacity && "Cannot shrink hashmap (data would be lost)");
    
    // The indicies of hashes rely on the capacity of the map. Therefore we
    // need to create a new, temporary hashmap and reinsert all elements.
    Hashmap *tmp = map;
    tmp->resize = false;

    vec_foreach(map->keys, i)
    {
        Key stored_key = vec_get(map->keys, i);
        if (!stored_key)
            continue;

        Value stored_value = vec_get(map->values, i);
        hashmap_insert(tmp, stored_key, stored_value);
    }
    
    vec_resize(map->keys, new_capacity);
    memcpy(map->keys->data, tmp->keys->data, tmp->keys->capacity);

    vec_resize(map->values, new_capacity);
    memcpy(map->values->data, tmp->values->data, tmp->values->capacity);
}

void hashmap_destroy(Hashmap *map)
{
    vec_deinit(map->keys);
    vec_deinit(map->values);
    free(map);
}
