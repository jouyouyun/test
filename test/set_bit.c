/*
 *	set || clear var N bit
 */

#include <stdio.h>

static int R;

void set_bit( unsigned int n )
{
	n = ( n > 31 ) ? ( n % 32 ) : n;

	R |= ( 1 << n );
}

void clear_bit( unsigned int n )
{
	n = ( n > 31 ) ? ( n % 32 ) : n;

	R &= ~( 1 << n );
}

int main()
{
	R = 0xde37;
	printf( "For example in 0x%x\n", R );
	set_bit(3);
	printf( "After set bit 3 is 0x%x\n", R );
	clear_bit(5);
	printf( "After clear bit 3 is 0x%x\n", R );

	return 0;
}
