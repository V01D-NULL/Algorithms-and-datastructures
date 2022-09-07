singly_linked_list:
	gcc linked_list/singly_linked_list.c linked_list/test/test_singly_linked_list.c -o build/singly_linked_list.elf
	./build/singly_linked_list.elf

Queue:
	gcc queue/queue.c queue/test/test_queue.c -o build/queue.elf
	./build/queue.elf

Vector:
	gcc vector/vector.c vector/test/test_vector.c -std=c11 -o build/vector.elf
	./build/vector.elf
