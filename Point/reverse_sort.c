/*
 ** 输入字符, 计算长度并反向排列
 */

#include "reverse.h"
#include<stdlib.h>

/*
 ** get_word() 输入字符
 */

char *get_word()
{
	int ch;
	int i = 0;
	int count = 1;
	char *s = (char*) malloc( sizeof(char) );

	while ( ch = getchar(), ch != -1 && ch != '\n' ) {
		s[i] = ch;
		s = realloc(s, ++count * sizeof(char) );
		i++;
	}

	return s;
}

/*
 ** len() 计算字符串的长度
 */

int len( char *s )
{
	int count = 0;

	while ( *s != '\0' ){
		count++;
		s++;
	}

	return count;
}

/*
 ** reverse_string() 反向排列
 */

void reverse_string( char *string )
{
	char ch;
	int  i, j, l;

	i = 1;
	j = 0;  /* 表示 *string 指向的位置 */
	l = len(string);
	while ( i <= (l / 2) ){
		ch = *(string + l - i - j );
		*( string + l - i - j) = *string;
		*string = ch;
		i++;
		j++;
		string++;
	}
}
