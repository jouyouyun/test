/* 判断使用的是大端还是小端 */

#include <stdio.h>

union un {
	unsigned int i;
	unsigned char c;
};

int main()
{
	union un u;

	u.i = 1;
	if ( u.c ) {
		printf( "小端\n" );
	} else {
		printf("大端\n");
	}

	return 0;
}
