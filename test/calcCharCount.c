#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void calcCharCount( char *s )
{
	int i = 0, j = 0, max = 0;
	int count[26] = { 0 };
	int flag = 0, flag2 = 0;

	/* 检查输入参数是否为空 */
	assert( s );

	for ( i = 0; s[i] != '\0'; i++ ) {
		if ( s[i] >= 'a' && s[i] <= 'z' ) {
			max = ( ++count[(int)s[i] - 97]) > max ? count[(int)s[i] - 97] :
				max;
			printf( "max = %d\n", max );
		}
	}

	for ( i = 1; i <= max; i++ ) {
		for ( j = 0; j < 25; j++ ) {
			if ( count[j] == i ) {
				printf( "%c", (char)(j + 97 ) );
				flag = 1;
			}
		}

		if ( flag ) {
			printf( " :%2d\n", i );
			flag = 0;
			flag2 = 1;
		}
	}

	if ( !flag2 ) {
		printf( "No matched!\n" );
	}
}

int main()
{
	char str[1024];

	printf( "请输入字符串:\n" );
	if ( fgets( str, sizeof(str), stdin ) == NULL ) {
		perror( "stdin err" );
		exit(-1);
	}

	calcCharCount( str );

	return 0;
}
