#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "single_linked_stack.h"

void move(int num_discs, struct Stack* source, struct Stack* destination,
		struct Stack* intermediate) {
	if (num_discs == 1) {
		push(destination, pop(source));
		printf("Move disk %i from %s to %s\n", destination->top->data, source->name, destination->name);
	} else {
		move(num_discs - 1, source, intermediate, destination);
		push(destination, pop(source));
		printf("Move disk %i from %s to %s\n", destination->top->data, source->name, destination->name);
		move(num_discs -1, intermediate, destination, source);
	}
	return;
}

int main(int argc, char *argv[]) {
	/*
	 * BEGIN OF ERROR-CHECKING
	 */
	if (argc < 3 || argc > 6) {
		//Invalid argument number
		printf("ERROR: Too many/not enough arguments!\n");
		printf("Usage: range_start range_end stack_A stack_B stack_C.\n");
		printf("System exiting with Code -1\n");
		exit(-1);
	}
	if (isdigit(*argv[1]) == 0 || isdigit(*argv[2]) == 0) {
		//Range 1 or 2 are not integers
		printf("ERROR: Invalid arguments!\n");
		printf("range_start and range_end must be integer values\n");
		printf("System exiting with Code -2\n");
		exit(-2);
	}
	if (*argv[1] < 0|| *argv[1] > INT_MAX || *argv[2] < *argv[1]
	|| *argv[2] > INT_MAX) {
		//argv[1] is smaller than 0 - argv[1] is larger than int_max - argv[2] is smaller than argv[1] - argv[2] is larger than int_max
		//Invalid range
		printf("ERROR: Invalid arguments!\n");
		printf("A positive non-zero number of disks is required.\n");
		printf("System exiting with Code -3\n");
		exit(-3);
	}
	//NOTE: The names are not checked, as they are completely optional and will be NULL, if not existent
	/*
	 * END OF ERROR-CHECKING
	 */

	/*
	 * START OF INITIALIZATION OF ALL VARIABLES
	 *
	 * We need:
	 * - 3 towers
	 * - range_end-range_start+1 Nodes
	 *
	 */

	//Creating stacks
	struct Stack *stack_a;
	//If there is no given name, just put in NULL
	if (argv[3] == NULL)
		stack_a = new_stack(NULL);
	else
		stack_a = new_stack(argv[3]);

	struct Stack *stack_b;
	//If there is no given name, just put in NULL
	if (argv[3] == NULL)
		stack_b = new_stack(NULL);
	else
		stack_b = new_stack(argv[4]);

	struct Stack *stack_c;
	//If there is no given name, just put in NULL
	if (argv[3] == NULL)
		stack_c = new_stack(NULL);
	else
		stack_c = new_stack(argv[5]);


	//node_number is a easy placeholder for argv[2]-argv[1]+1. It just makes things more simple
	int node_number;
	node_number = *argv[2] - *argv[1] +1;

	//Assigning nodes
	for (int i = node_number; i > 0; i--) {
		push_value(stack_a, i);
	}

	/*
	 * END OF INITIALIZATION OF ALL VALUES
	 */

	/*
	 * START OF THE LIST-PRINTING
	 */
	printf("***** BEFORE SOLVING *****\n\n");

	printf("Tower %s\n", stack_a->name);
	print_stack(stack_a);

	printf("\nTower %s\n", stack_b->name);
	print_stack(stack_b);

	printf("\nTower %s\n", stack_c->name);
	print_stack(stack_c);

	printf("\n***** SOLVING PUZZLE *****\n\n");
	/*
	 * END OF THE LIST-PRINTING
	 */

	/*
	 * move() IS CALLED
	 */

	move(node_number, stack_a, stack_c, stack_b);
	/*
	 * move() HAS BEEN CALLED
	 */

	/*
	 * START OF THE NEW LIST-PRINTING
	 */
	printf("\n***** AFTER SOLVING *****\n\n");

	printf("Tower %s\n", stack_a->name);
	print_stack(stack_a);

	printf("\n\nTower %s\n", stack_b->name);
	print_stack(stack_b);

	printf("\n\nTower %s\n", stack_c->name);
	print_stack(stack_c);

	printf("\n***** PUZZLE SOLVED *****\n\n");
	/*
	 * END OF THE NEW LIST-PRINTING
	 */

	/*
	 * TIME TO FREE THE MEMORY
	 */
	clear_stack(stack_a);
	clear_stack(stack_b);
	clear_stack(stack_c);

	free((void*) stack_a);
	free((void*) stack_b);
	free((void*) stack_c);
	/*
	 * THE MEMORY HAS BEEN FREEDOM-IZED
	 * MURICA, FUCK YEA!
	 */

	exit(0);
}
