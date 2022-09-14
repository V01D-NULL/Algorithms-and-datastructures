CC_FLAGS = -g # -D VERBOSE

singly_linked_list:
	@gcc $(CC_FLAGS) linked_list/singly_linked_list.c linked_list/test/test_singly_linked_list.c -o build/singly_linked_list.elf
	@./build/singly_linked_list.elf

Queue:
	@gcc $(CC_FLAGS) queue/queue.c queue/test/test_queue.c -o build/queue.elf
	@./build/queue.elf

Vector:
	@gcc $(CC_FLAGS) vector/vector.c vector/test/test_vector.c -o build/vector.elf
	@./build/vector.elf

Deque:
	@gcc $(CC_FLAGS) vector/vector.c deque/deque.c deque/test/test_deque.c -o build/deque.elf
	@./build/deque.elf

Hashmap:
	@gcc $(CC_FLAGS) hashmap/hashmap.c vector/vector.c hashmap/test/test_hashmap.c -o build/hashmap.elf
	@./build/hashmap.elf

BinarySearchTree:
	@gcc $(CC_FLAGS) bst/bst.c bst/test/test_bst.c bst/displayTree.c -lm -o build/BinarySearchTree.elf
	@./build/BinarySearchTree.elf

RedBlackTree:
	@gcc $(CC_FLAGS) rbtree/rbtree.c rbtree/rbvalidate.c rbtree/test/test_rbtree.c rbtree/displayTree.c -lm -o build/RedBlackTree.elf
	@./build/RedBlackTree.elf