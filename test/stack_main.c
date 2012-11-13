/*
 * stack main
 */

#include "stack.h"

int main()
{
	int i;

	create();

	for ( i = 2; i <= 6; i++ ) {
		push_stack(i);
	}
	printf( "top: %d\n", get_top() );

	for ( i = 0; i < 2; i++ ) {
		printf( "pop: %d\n", pop_stack() );
	}
	printf( "top: %d\n", get_top() );

	destroy_stack();
	if ( empty_stack() ) {
		printf( "destroy stack success!\n" );
	}

	return 0;
}
