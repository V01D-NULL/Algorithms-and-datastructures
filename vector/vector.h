#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>

typedef struct __vector
{
	uint64_t **data;
	int capacity;
	int elements;
} Vector;

#define vec_foreach(vector, index) \
	for (int index = 0; index < vector->elements; index++)

Vector *vec_init(int capacity);
void *vec_front(Vector *v);
void *vec_back(Vector *v);
void vec_push_back(Vector *v, void *data);
void vec_pop_back(Vector *v);
void vec_resize(Vector *v, int new_size);
void *vec_get(Vector *v, int index);
void vec_insert(Vector *v, int a, int b, void *data);
void vec_deinit(Vector *v);

#endif // VECTOR_H