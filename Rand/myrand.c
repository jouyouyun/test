#include "myrand.h"

static unsigned long next = 1;

/* RAND_MAX assumed to be 32767 */
int myrand( void ) 
{
	next = next * 1103515245 + 12345;

	return ( (unsigned ) ( next / 65536 ) % 32768 );
}

void mysrand( unsigned seed )
{
	next = seed;
}
