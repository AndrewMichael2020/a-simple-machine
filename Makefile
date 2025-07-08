simple_machine: simple_machine.c
	gcc -o simple_machine simple_machine.c

rpn_calculator: rpn_calculator.c
	gcc -o rpn_calculator rpn_calculator.c

preprocessor_examples: preprocessor_examples.c
	gcc -o preprocessor_examples preprocessor_examples.c

simplest_recursive_function: simplest_recursive_function.c
	gcc -o simplest_recursive_function simplest_recursive_function.c

clean:
	rm -f simple_machine rpn_calculator preprocessor_examples simplest_recursive_function

