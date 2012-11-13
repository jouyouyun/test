/*
 *	将 IP 地址转化为十六进制整数
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int cip2unit( char cip[] )
{
	unsigned int uip = 0;
	int i, j;
	char *p;

	if ( strlen(cip) > 15 || strlen(cip) < 7 ) {
		printf ( "输入的不是 IP 地址错误!\n" );
		exit(-1);
	}
	/*以 '.' 来分割字符串 */
	p = strtok( cip, "." );
	for ( uip = i = 0; i < 4 && p; ++i ) {
		if ( strlen( p ) > 3 ) {
			printf( "argument error!\n" );
			exit(-1);
		}
		/* 把字符串转化为整数 */
		j = atoi(p);
		if ( j < 0x00 || j > 0xff ) {
			return 0;
		}
		uip <<= 8;
		uip += j;
		p = strtok( NULL, "." );
	}

	return ((((uip) & 0xff000000) >> 24 ) | 
		(((uip) & 0x00ff0000) >> 8) | 
		(((uip) & 0x0000ff00) << 8) | 
		(((uip) & 0x000000ff) << 24));
}

int main()
{
	char ip[15];
	unsigned int uip = 0;

	scanf( "%s", ip );
	uip = cip2unit( ip );
	printf( "%.8X\n", uip );

	return 0;
}
