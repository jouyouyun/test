#include <stdio.h>

#define max(x,y)	((x>y)?x:y)

int main()
{
	int x = 5, y = 4;
	int z = max(x++, y++);
	printf( "x = %d\n", x );
	return 0;
}
