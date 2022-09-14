# Algorithms-and-datastructures

### Implemented:
- Singly linked list
- Queue using a doubly linked list (Amortized queue)
- Vector (as in a dynamically resizable array, similar to C++'s std::vector)
- Deque using a vector
- Hashmap (Keys must all be equal in length¹, uses a dynamic array (vector) and open addressing (linear probing) for collision resolution)
- Standard Binary search tree
- Red black tree

### Future ideas:
- The hashmap should use the red black tree for collision resolution which will result in increased performance
- sorting algorithm(s) (I'm not sure which one, but I do want to add something like that)

¹ This is due to the hashing algorithm used for this hashmap implementation. A different hashing algorithm can resolve this potential obstruction if variable length keys are required.