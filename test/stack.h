/*
 * link stack
 */

#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>

typedef struct stack {
	int e;
	struct stack *next;
}STACK;

STACK *ptop;

STACK *get_node(int e);
void create();
int empty_stack();
void push_stack(int e);
int pop_stack();
int get_top();
void destroy_stack();

#endif
