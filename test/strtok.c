/*
 * Test strtok 分割字符串
 */

#include <stdio.h>
#include <string.h>

int main( int argc, char *argv[] )
{
	char *p;

	if ( argc != 2 ) {
		printf( "Usage: %s path\n", argv[0] );
		return -1;
	}

	printf( "str: %s\n", argv[1] );

	printf( "%s\n", strtok( argv[1], "/" ) );
	while ( ( p = strtok(NULL, "/") ) ) {
		printf( "%s\n", p );
	}

	return 0;
}
