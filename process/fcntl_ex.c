/*
 *	使用 fcntl 实现进程互斥
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main( int argc, char *argv[] )
{
	int fd;
	int count = 0;
	struct flock lock;

	if ( argc != 2 ) {
		printf( "Usages: %s filename\n", argv[0] );
		exit(-1);
	}

	/* 执行可执行程序的参数为加锁文件，首先获得其文件描述符 */
	if ( (fd = open( argv[1], O_RDWR )) == -1 ) {
		perror( "Cannot open the file" );
		exit(-1);
	}

	/*
	 *	使用 F_SETLK 参数需要设置 flock 结构提中的一些变量
	 *	下面给出具体设置：
	 *	设置写锁
	 */
	lock.l_type = F_WRLCK;

	/* 从文件起始处开始 */
	lock.l_whence = 0;

	/* 偏移值为 0 */
	lock.l_start = 0;

	/* 给整个文件加锁 */
	lock.l_len = 0;

	/* 
	 *	调用 fcntl 函数，如果失败，sleep 1s，然后再次调用 
	 *	重复次数为5次
	 */
	while ( fcntl( fd, F_SETLK, &lock ) < 0 ) {
		switch( errno ) {
			case EAGAIN:
			case EACCES:
				if ( ++count < 5 ) {
					sleep(1);
				} else {
					fcntl( fd, F_GETLK, &lock );
					printf( "pid:%ld process find pid:%ld lock the file %s\n",
							(long)getpid(), (long)lock.l_pid, argv[1] );
					return 1;
				}
				continue;
		}
		perror( "function fcntl call fail" );
		exit(-1);
	}

	printf( "pid: %ld process lock the file\n", (long)getpid() );
	sleep(2);
	printf( "pid: %ld process release the file\n", (long)getpid() );

	return 0;
}
