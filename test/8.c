#include <stdio.h>
#include <stdlib.h>

int func( int n )
{
	if ( n <= 0 ) {
		printf( "err number\n" );
		exit(-1);
	}
	
	if ( n == 1 ) {
		n = 2;
	} else if ( n == 2 ) {
		n = 3;
	} else if ( n == 3 ) {
		n = 8;
	} else {
		n = func(n-1) + func(n-2) +n;
	}
	
	return n;
}

int main()
{
	int s1 = 0, s2 = 0;
	int sum = 0;
	
	s1= func(36);
	s2 = func(31);
	sum = s1 + s2;
	
	printf( "sum = %d\n", sum );
	
	return 0;
}
