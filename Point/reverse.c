/*
 ** 编写函数 reverse_string( char *string ); 函数把参数字符串中的字符反向
 ** 排列, 请使用指针而不是数组下标，不要使用任何 C 函数库中操作字符串的
 ** 函数，提示：不需要声明一个局部数组来临时存储参数字符串。
 */

#include "reverse.h"
#include<stdlib.h>

int main()
{
	char** s = (char**) malloc( sizeof(char*) );

	s[0] = get_word();
	printf("反向排列之前：%s\n", s[0]);
	/* 反向排列 */
	reverse_string(s[0]);

	/* 输出结果 */
	printf("反向排列之后：%s\n", s[0]);

	/* 释放内存 */
	free(s[0]);
	free(s);

	return 0;
}
