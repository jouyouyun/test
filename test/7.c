#include <stdio.h>

int main()
{
	int i, j;
	int s = 0;

	for ( i = 2; i <= 9958; i++ ) {
		for ( j = 2; j < i; j++ ) {
			if ( i % j == 0 ) {
				break;
			}
		}
		if ( j >= i ) {
			s += i;
		}
	}

	printf("s = %d\n", s);

	return 0;
}
