#include <stdio.h>

char mytoupper( char c )
{
	if ( c >= 'a' && c <= 'z' ) {
		return ( c - 'a' + 'A' );
	} else {
		return c;
	}
}

int main()
{
	int i = 0;
	char str[] = "This a Test!";

	while ( str[i] != '\0' ) {
		str[i] = mytoupper(str[i]);
		i++;
	}

	printf( "%s\n", str );
	return 0;
}


