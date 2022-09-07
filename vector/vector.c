#include "vector.h"
#include <stdlib.h>
#include <assert.h>

#define __vec_ensure_capacity(v) assert((v->elements > 0 && v->elements <= v->capacity) && "Vector is empty")

Vector *vec_init(int capacity)
{
    Vector *v = malloc(sizeof(Vector));
    v->capacity = capacity;
    v->elements = 0;
    v->data = malloc(sizeof(int) * capacity);
    return v;
}

int vec_front(Vector *v)
{
    __vec_ensure_capacity(v);
    return v->data[0];
}

int vec_back(Vector *v)
{
    __vec_ensure_capacity(v);
    return v->data[v->elements - 1];
}

void vec_push_back(Vector *v, int data)
{
    if (v->elements == v->capacity)
        vec_resize(v, v->capacity * 2);

    v->data[v->elements++] = data;
}

void vec_pop_back(Vector *v)
{
    __vec_ensure_capacity(v);
    v->data[v->elements - 1] = 0;
    --v->elements;
}

void vec_resize(Vector *v, int new_size)
{
    v->capacity = new_size;
    v->data = realloc(v->data, sizeof(int) * new_size);
    assert(v->data && "Failed to resize vector");
}

int vec_get(Vector *v, int index)
{
    __vec_ensure_capacity(v);
    assert(index <= v->elements - 1 && "Invalid index");
    return v->data[index];
}

// Insert 'data' between index 'a' and 'b'
void vec_insert(Vector *v, int a, int b, int data)
{
    __vec_ensure_capacity(v);
    assert((a >= 0 && a <= v->elements - 1) && "index out of range");
    assert((b >= 0 && b <= v->elements - 1) && "index out of range");

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

void vec_deinit(Vector *v)
{
    free(v->data);
    free(v);
}
