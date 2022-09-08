#include "../vector.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/* Create vector */
	Vector *v = vec_init(1);

	/* Push '123' and '456' to the tail of the vector */
	printf("Pushing 123 and 456 to the vector\n\n");
	vec_push_back(v, (void *)123);
	vec_push_back(v, (void *)456);

	/* Print all elements in the vector */
	printf("Iterating over vector:\n");
	vec_foreach(v, i)
	{
		printf("vector[%d] = %d\n", i, vec_get(v, i));
	}

	/* Remove an element from the tail from the vector */
	printf("Popping element from the tail of the vector\n\n");
	vec_pop_back(v);

	/* Print all elements in the vector */
	printf("Iterating over vector:\n");
	vec_foreach(v, i)
	{
		printf("vector[%d] = %d\n", i, vec_get(v, i));
	}

	/* Push '456' and '789' to the tail of the vector */
	printf("Pushing 456 and 789 to the vector\n\n");
	vec_push_back(v, (void *)456);
	vec_push_back(v, (void *)789);

	/* Print values at the head and tail of the vector */
	printf("front: %d | back: %d\n", (int)vec_front(v), (int)vec_back(v));
	vec_foreach(v, i)
	{
		printf("vector[%d] = %d\n", i, vec_get(v, i));
	}

	/* Retrieve a value using random access */
	printf("Performing random access (index 1): %d\n", vec_get(v, 1));

	/* 123, 999, 456, 789 */
	printf("Inserting 999 between 123 and 456\n");
	vec_insert(v, 0, 1, (void *)999);
	vec_foreach(v, i)
	{
		printf("vector[%d] = %d\n", i, vec_get(v, i));
	}

	vec_deinit(v);
	return 0;
}