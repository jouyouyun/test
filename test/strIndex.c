/*
 * 模式匹配
 */

#include <stdio.h>

#define MAX_LEN 128

int strLength(const char *str);
int strIndex(const char *src, const char *sub);

int main()
{
	int lc;
	char src[MAX_LEN];
	char sub[MAX_LEN];

	printf( "Please Enter src: " );
	fgets( src, MAX_LEN, stdin );
	fflush(stdin);
	printf( "Please Enter sub: " );
	fgets( sub, MAX_LEN, stdin );

	lc = strIndex( src, sub );
	if ( lc == -1 ) {
		printf( "strIndex err!\n" );
	} else {
		printf( "lc = %d\n", lc );
	}

	return 0;
}

int strLength( const char *str)
{
	int i = 0;

	if ( str == NULL ) {
		return -1;
	}

	while ( str[i] != '\0' ) {
		i++;
	}

	/*
	 * 因使用 fgets 进行输入，所以每个字符串后面带有 '\n'
	 */
	return (i - 1);
}

int strIndex( const char *src, const char *sub)
{
	int i = 0, j = 0;
	int src_len, sub_len;

	if ( src == NULL || sub == NULL ) {
		return -1;
	}

	if ( (src_len = strLength(src)) == -1 ) {
		return -1;
	}
	if ( (sub_len = strLength(sub)) == -1 ) {
		return -1;
	}

	if ( src_len < sub_len ) {
		return -1;
	}

	while ( i < src_len && j < sub_len ) {
		if ( *(src + i) == *sub ) {
			j++;
			while ( j < sub_len ) {
				if ( *(src +i +j) != *(sub + j) ) {
					j = 0;
					break;
				}
				j++;
			}
		}
		i++;
	}

	if ( j == sub_len ) {
		return (i - 1);
	} else {
		return 0;
	}
}
