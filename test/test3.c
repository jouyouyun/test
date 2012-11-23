/*
 * str[] = "12345";
 * p = str + 1;
 * strcpy( p, "ABC" );
 * strlen(p) = ?
 */

#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "1234356789";
	char *p = str + 2;

	strcpy( p, "ABC" );
	printf( "%s\t%d\n", str, (int)strlen(p) );

	return 0;
}
