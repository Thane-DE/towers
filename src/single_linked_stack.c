#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "single_linked_stack.h"

struct Stack *new_stack(char* name) {
	struct Stack *new_stack; //Creates a new Stack
	new_stack = (struct Stack*) malloc(sizeof(struct Stack)); //Allocates the memory
	new_stack->name = name;
	new_stack->top = NULL;
	return new_stack;
}

void push_value(struct Stack* the_stack, int value) {
	//Creates a new Node for the value and assigns it
	struct Node *new_node;
	new_node = (struct Node*) malloc(sizeof(struct Node));
	new_node->data = value;
	new_node->next = NULL;

	//Pushes the newly created node onto the stack
	push(the_stack, new_node);
}

void push(struct Stack* the_stack, struct Node* new_node) {
	//Temporary pointer used for the assignment
	struct Node *tmp_ptr;
	tmp_ptr = the_stack->top;

	//Checks if there is a top pointer in the Stack
	if (the_stack->top == NULL) {
		//Pushes the node onto the stack
		the_stack->top = new_node;
		return;
	}
	//IF the value is smaller -> insert as new head. Inserting in the middle or below is NOT an option.
	if (new_node->data < the_stack->top->data) {
		//Insert as new head
		new_node->next = tmp_ptr;
		the_stack->top = new_node;
		return;
	} else {
		printf("ERROR: Node can't be inserted at the bottom of a stack!\n");
		return;
	}
}

struct Node* pop(struct Stack* the_stack) {
	//Temporary node
	struct Node* return_node;

	//In case the stack is literally empty
	if (the_stack->top == NULL) {
		printf("ERROR: The stack is already empty!");
		return 0;
	}
	//In case there is only a top node
	if (the_stack->top->next == NULL) {
		return_node = the_stack->top;
		the_stack->top = NULL;
		return return_node;
	}
	//If there are other values
	struct Node* temporary_old;
	temporary_old = the_stack->top;

	the_stack->top = temporary_old->next;
	temporary_old->next = NULL;

	return temporary_old;
}

void clear_stack(struct Stack* the_stack) {
	struct Node* iterator;
	struct Node* iterator_next;

	iterator = the_stack->top;

	//Just in case there only is a TOP value
	if (the_stack->top->next == NULL) {
		free((void*) the_stack->top);
		the_stack->top = NULL;
		return;
	}

	//Sets the Stack to empty
	the_stack->top = NULL;

	//Time to free this shit
	while (1) {

		if (iterator->next == NULL) {
			//AKA there is nothing after the current iterator anymore, so we're finished
			free((void*) iterator);
			return;
		}
		iterator_next = iterator->next; //The Node after the current one is saved

		free((void*) iterator);

		iterator = iterator_next; //The next node is inserted into "iterator"
	}
}

void print_stack(struct Stack* the_stack) {
	struct Node* iterator_2;
	iterator_2 = the_stack->top;

	printf("--TOP--\n");

	while (1) {
		if (iterator_2 == NULL) {
			printf("--BOTTOM--\n");
			return;
		}
		printf("%i\n", iterator_2->data);
		if (iterator_2->next == NULL) { //If this is the last one
			printf("--BOTTOM--\n");
			return;
		}
		iterator_2 = iterator_2->next; //If not, just get the next one
	}
}
