#include <stdio.h>

void main()
{
	static char a[] = "computer";
	static char b[] = "compare";
	char *p = a;
	char *q = b;
	int j;
	
	for ( j = 0; j < 7; j++ ) {
		if ( *(p + j ) == *(q  +j))
		{
			printf("%c", *(p + j));
		}
	}
}
