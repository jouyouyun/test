#include <stdio.h>
#include <sys/stat.h>

int main( int argc, char* argv[] )
{
	/*
	 * 判断程序参数个数，如果带有一个参数，执行符合要求
	 * 否则给出相应的提示信息
	 */
	if ( argc != 2 ) {
		printf("Usage: %s filename\n", argv[0] );
		return 1;
	}
	
	/* 调用 chmod 函数，将文件权限修改为“r--r--r-x”形式 */
	if( chmod(argv[1], S_IRUSR | S_IRGRP | S_IXOTH | S_IROTH) < 0 ) {
		perror("Cannot modify the Permission of the file");
		return 1;
	}
	
	return 0;
}
