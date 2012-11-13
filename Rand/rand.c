#include "myrand.h"
#include <stdio.h>
int main()
{
	int i;

	for ( i = 0; i < 10; i++ )
		printf( "%d\t", myrand() % ( 60 - 20 + 1 ) + 20 );

	return 0;
}
