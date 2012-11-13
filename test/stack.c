#include "stack.h"
#include <stdlib.h>

STACK *get_node(int e)
{
	STACK *pnode = (STACK*)malloc(sizeof(STACK));

	if ( pnode == NULL ) {
		perror( "malloc err" );
		exit(-1);
	}

	pnode->e = e;
	pnode->next = NULL;

	return pnode;
}

void create()
{
	ptop = NULL;
}

void push_stack(int e)
{
	STACK *pnode = get_node(e);

	pnode->next = ptop;
	ptop = pnode;
}

int empty_stack()
{
	if ( ptop == NULL ) {
		return 1;
	} else {
		return 0;
	}
}

int pop_stack()
{
	int e;
	STACK *ptemp;

	if ( ptop == NULL ) {
		printf( "stack empty!\n" );
		exit(-1);
	}

	ptemp = ptop;
	ptop = ptop->next;
	e = ptemp->e;
	free(ptemp);

	return e;
}

int get_top()
{
	if ( ptop == NULL ) {
		printf( "stack empty!\n" );
		exit(-1);
	}

	return ptop->e;
}

void destroy_stack()
{
	STACK *pfree;

	while ( !empty_stack() ) {
		pfree = ptop;
		ptop = ptop->next;
		free(pfree);
	}
}
