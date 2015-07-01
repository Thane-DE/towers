/*
 * dblink_list.h
 *
 *  Created on: Jun 24, 2015
 *      Author: hoeselm
 */

#ifndef SINGLE_LINKED_STACK_H_
#define SINGLE_LINKED_STACK_H_

struct Node {
	int data;
	struct Node* next;
};
struct Stack {
	struct Node* top;
	char* name;
};

struct Stack* new_stack(char* name);

void push_value(struct Stack* the_stack, int value);

void push(struct Stack* the_stack, struct Node* new_node);

struct Node* pop(struct Stack* the_stack);

void clear_stack(struct Stack* the_stack);

void print_stack(struct Stack* the_stack);

#endif /* SINGLE_LINKED_STACK_H_ */
