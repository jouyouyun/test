/*
 *	通过地址来比较两个变量的值是否相等
 */

#include <stdio.h>
#include <string.h>

typedef struct test {
	int a;
	char c;
} TEST;

int main()
{
	TEST A, B;
	A.a = 4, B.a = 4;

	if ( memcmp( &A, &B, sizeof(TEST) ) == 0 ) {
		printf( "Equal!\n" );
	} else {
		printf( "Not Equal!\n" );
	}

	return 0;
}
