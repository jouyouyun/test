/*
 ** 冒泡 字符串
 */

#include<stdio.h>
#include<string.h>

#define MAX 100

int sort(char *s);

int main()
{
	char str[MAX];

	printf("请输入一串字符串：");
	gets(str);

	sort(str);
	printf("排序后的字符串为：");
	puts(str);

	return 0;
}

int sort(char *s)
{
	char ch;
	int i, j, len;

	len = strlen(s);
	for ( i = 0; i < len; i++ ){
		for ( j = len - 1; j > 0; j-- ){
			if ( *(s + j - 1) > *(s + j)){
				ch = *(s + j - 1);
				*(s + j - 1) = *(s + j);
				*(s + j) = ch;
			}
		}
	}

	return 0;

}
