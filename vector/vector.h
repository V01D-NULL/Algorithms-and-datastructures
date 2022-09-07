#ifndef VECTOR_H
#define VECTOR_H

typedef struct __vector {
  int *data;
  int capacity;
  int elements;
} Vector;

#define vec_foreach(vector, index)                                             \
  for (int index = 0; index < vector->elements; index++)

Vector *vec_init(int capacity);
int vec_front(Vector *v);
int vec_back(Vector *v);
void vec_push_back(Vector *v, int data);
void vec_pop_back(Vector *v);
void vec_resize(Vector *v, int new_size);
int vec_get(Vector *v, int index);
void vec_insert(Vector *v, int a, int b, int data);
void vec_deinit(Vector *v);

#endif // VECTOR_H