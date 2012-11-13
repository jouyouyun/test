#include <stdio.h>
#define MAXLEN	50

/* 用来存储计算阶乘后为数的数组 */
int data[MAXLEN];

int calcfact( int n )
{
	int i, j, k, r;	/* 循环计数变量 */
	int digit = 1;	/* 数据位数变量 */

	for ( i = 1; i < MAXLEN + 1; i++ ) {
		data[i] = 0;
	}
	data[0] = 1;
	data[1] = 1;

	for ( i = 1; i < n + 1; i++ ) {
		for ( j = 1; j < digit + 1; j++ ) {
			data[j] *= i;	/* 计算阶乘 */
		}

		for ( j = 1; j < digit + 1; j++ ) {
			if ( data[j] > 10 ) {
				for ( r = 1; r < digit + 1; r++ ) {
					if ( data[digit] > 10 ) {
						digit++;	/* 当数组中的值大于10则位数加1 */
					}

					data[r + 1] += data[r] / 10;
					data[r] = data[r] % 10;
				}
			}
		}

		printf( "%d != ", i );
		for ( k = digit; k > 0; k-- ) {
			printf( "%d", data[k] );
		}
		printf( "\n" );
	}

	//return data;
	return 0;
}

int main()
{
	int n;

	printf( "Enter a number: " );
	scanf( "%d", &n );
	calcfact(n);

	return 0;
}
