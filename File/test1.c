/*
 * fopen() Test
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define MYFILE "missing.txt"

int main()
{
	/* 定义句柄 */
	FILE *fop;

	/* 以读的方式打开文件 */
	fop = fopen(MYFILE, "r");

	/* 检查打开是否失败 */
	if ( fop == (FILE *)NULL ) {
		printf("%s: %s\n", MYFILE, strerror( errno ));
		exit(-1);
	}

	/* 关闭文件 */
	fclose( fop );

	return 0;
}

