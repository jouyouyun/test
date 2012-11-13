#include <stdio.h>
#include <math.h>

int main()
{
	int i;
	float tmp, num;
	
	for ( i = 1; i < 18954; i++ ) {
		tmp = pow(712, i);
		num = tmp % 1000;
		//printf( "num = %f\n", tmp);
		if ( num == 696 ) {
			printf( "tmp = %f, i = %d\n", tmp, i );
			break;
		}
	}
	
	return 0;
}
