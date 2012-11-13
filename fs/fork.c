/*
 ** open()
 ** read()
 ** fork()
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
	char test;
	/* fd 用来保存打开文件的文件描述符 */
	int fd;

	/*
	 ** 使用 open 函数打开文件
	 ** 如果打开失败则给出相关的失败信息，程序返回
	 */
	if ( (fd = open( "pwd.c", O_RDONLY )) == -1 ) {
		perror( "Cannot open the pwd.c file !" );
		return 1;
	}

	/* 调用 fork 函数产生子进程 */
	if ( fork() == -1 ) {
		perror( "Cannot create the child process !" );
		return 1;
	}

	/* 读取 pwd.c 文件中的一个字符，保存在 test 变量中 */
	read( fd, &test, 1 );

	/* 输出结果，函数 getpid 会获得进程的进程号 */
	printf( "Process ID : %ld read the character : %c\n", 
			(long)getpid(), test );

	/* 关闭文件，注意这里父子进程都分别关闭一次 */
	close( fd );

	return 0;
}
