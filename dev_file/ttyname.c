#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main ()
{
	/*
	 *  定义三个指针来分别保存标准输入、标准输出和
	 *  标准错误输出的终端名
	 */
	char *tty_stdin_name;
	char *tty_stdout_name;
	char *tty_error_name;

	/*
	 *  调用 ttyname 函数来获取终端的名称，如果失败，返回 NULL
	 */
	if ( (tty_stdin_name = ttyname(STDIN_FILENO)) == NULL ) {
		perror( "Cannot get tty_stdin_name" );
		exit(-1);
	}
	/* 打印出获得的终端名称 */
	printf ( "tty_stdin_name : %s\n", tty_stdin_name );

	if ( (tty_stdout_name = ttyname(STDOUT_FILENO)) == NULL ) {
		perror( "Cannot get tty_stdout_name" );
		exit(-1);
	}
	/* 打印出获得的终端名称 */
	printf ( "tty_stdout_name : %s\n", tty_stdout_name );

	if ( (tty_error_name = ttyname(STDERR_FILENO)) == NULL ) {
		perror( "Cannot get tty_error_name" );
		exit(-1);
	}
	/* 打印出获得的终端名称 */
	printf ( "tty_error_name : %s\n", tty_error_name );

	return 0;
}
