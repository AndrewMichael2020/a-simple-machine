all: simple_machine rpn_calculator preprocessor_examples simplest_recursive_function concat linked_list_delete linked_list_reverse py_rstrip py_lstrip touring_machine union_demo hash_table_lookup binary_tree_wordcount point_oop_demo pystr_demo pylist_demo pydict_demo

simple_machine: simple_machine.c
	gcc -o simple_machine simple_machine.c

rpn_calculator: rpn_calculator.c
	gcc -o rpn_calculator rpn_calculator.c

preprocessor_examples: preprocessor_examples.c
	gcc -o preprocessor_examples preprocessor_examples.c

simplest_recursive_function: simplest_recursive_function.c
	gcc -o simplest_recursive_function simplest_recursive_function.c

concat: concat.c
	gcc -o concat concat.c

linked_list_delete: linked_list_delete.c
	gcc -o linked_list_delete linked_list_delete.c

linked_list_reverse: linked_list_reverse.c
	gcc -o linked_list_reverse linked_list_reverse.c

py_rstrip: py_rstrip.c
	gcc -o py_rstrip py_rstrip.c

py_lstrip: py_lstrip.c
	gcc -o py_lstrip py_lstrip.c

touring_machine: touring_machine.c
	gcc -o touring_machine touring_machine.c

union_demo: union_demo.c
	gcc -o union_demo union_demo.c

hash_table_lookup: hash_table_lookup.c
	gcc -o hash_table_lookup hash_table_lookup.c

binary_tree_wordcount: binary_tree_wordcount.c
	gcc -o binary_tree_wordcount binary_tree_wordcount.c

point_oop_demo: point_oop_demo.c
	gcc -o point_oop_demo point_oop_demo.c -lm

pystr_demo: pystr_demo.c
	gcc -o pystr_demo pystr_demo.c

pylist_demo: pylist_demo.c
	gcc -o pylist_demo pylist_demo.c

pydict_demo: pydict_demo.c
	gcc -o pydict_demo pydict_demo.c

clean:
	rm -f simple_machine rpn_calculator preprocessor_examples simplest_recursive_function concat linked_list_delete linked_list_reverse py_rstrip py_lstrip touring_machine union_demo hash_table_lookup binary_tree_wordcount point_oop_demo pystr_demo pylist_demo pydict_demo

