Data Structures in C++

Stacks
Queues
Binary Search Tree
Heap Tree
Graphs

Compiling Examples

linked_list_main: g++49 -I includes/ src/llist.cpp  tests/llist_main.cpp
    - requires el_t to be 'int' in includes/llist.h

slist_main: g++49 -I includes/ src/llist.cpp src/slist.cpp tests/slist_main.cpp
    - requires el_t to be 'int' in includes/llist.h

queue_main: g++49 -I includes/ src/queue.cpp tests/queue_main.cpp
    - requires el_t to be 'string' in includes/queue.h

bst_main: g++49 -I includes/ tests/bst_main.cpp

array_to_bst: g++49 -I includes/ tests/array_to_bst.cpp

avl_main: g++49 -I includes/ tests/avl_main.cpp
