#include "vector.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define __vec_ensure_capacity(idx) assert((idx >= 0 && idx <= v->capacity) && "Vector is empty")

Vector *vec_init(int capacity)
{
    Vector *v = calloc(1, sizeof(Vector));
    v->capacity = capacity;
    v->elements = 0;
    v->data = malloc(sizeof(void *) * capacity);
    return v;
}

void *vec_front(Vector *v)
{
    __vec_ensure_capacity(0);
    return v->data[0];
}

void *vec_back(Vector *v)
{
    __vec_ensure_capacity(v->elements - 1);
    return v->data[v->elements - 1];
}

void vec_push_back(Vector *v, void *data)
{
    if (v->elements == v->capacity)
        vec_resize(v, v->capacity * 2);

    v->data[v->elements++] = data;
}

void vec_pop_back(Vector *v)
{
    __vec_ensure_capacity(v->elements - 1);
    vec_remove(v, v->elements - 1);
}

void vec_resize(Vector *v, int new_size)
{
    if (new_size <= 0)
        return;

    v->capacity = new_size;
    v->data = reallocarray(v->data, sizeof(void *), new_size);
    assert(v->data && "Failed to resize vector");
}

void *vec_get(Vector *v, int index)
{
    __vec_ensure_capacity(index);
    return v->data[index];
}

// Insert 'data' between index 'a' and 'b'
void vec_insert(Vector *v, int a, int b, void *data)
{
    assert((a >= 0 && a <= v->capacity - 1) && "index out of range");
    assert((b >= 0 && b <= v->capacity - 1) && "index out of range");

    ++v->elements;
    if (v->elements > v->capacity)
        vec_resize(v, v->capacity * 2);

    for (int i = v->elements; i >= b; i--)
    {
        v->data[i] = v->data[i - 1];
    }

    // Inserting data between equal indicies (i.e. a==b)
    // is the same as replacing the data at that index.
    if (a == b)
        v->data[a] = data;
    else
        v->data[a + 1] = data;
}

void vec_remove(Vector *v, int at)
{
    assert((at >= 0 && at <= v->capacity - 1) && "index out of range");
    memmove(&(v->data[at]), &(v->data[at + 1]), v->elements - at - 1);
    vec_resize(v, --v->elements);
}

void vec_emplace(Vector *v, int at, void *data)
{
    __vec_ensure_capacity(at);
    v->data[at] = data;
}

void vec_deinit(Vector *v)
{
    free(v->data);
    free(v);
}
