/*
 *	使用文件实现进程互斥
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/*
 *	获得资源的访问权限，返回 1，表示可以访问，否则不能
 */

int get_access_right( int inq_interval, int retry_time, char *file_name )
{
	int fd;
	int count = 0;

	/* 调用 creat 函数判断文件是否存在 */
	fd = creat( file_name, 0 );

	/* 如果返回失败，进入 while 循环，重复一定次数 */
	while ( fd == -1 && errno == EACCES ) {
		printf( "pid: %ld process try to get access right ...\n", (long)getpid() );

		if ( ++count < retry_time ) {
			sleep( inq_interval );
		} else {
			return -1;
		}
		fd = creat( file_name, 0 );
	}

	close(fd);
	if ( fd != -1 ) {
		return 1;
	} else {
		return -1;
	}
}

/* 删除产生的标志文件 */
int release_right( char *file_name )
{
	int result;

	result = remove( file_name );
	if ( result == 0 ) {
		return 1;
	} else {
		return -1;
	}
}

int main( int argc, char *argv[] )
{
	int len;
	int count = 0;
	int retry_time, inq_interval;

	/* 判断是否输入了足够的参数 */
	if ( argc != 4 ) {
		printf( "Usage: %s retry_time inq_interval file_name\n", argv[0] );
		exit( -1 );
	}

	/* 进行参数转换 */
	retry_time = atoi( argv[1] );
	if ( retry_time <= 0 ) {
		printf( "illegal retry_time!\n" );
		exit(-1);
	}

	inq_interval = atoi( argv[2] );
	if ( inq_interval <= 0 ) {
		printf( "illegal inq_interval!\n" );
		exit(-1);
	}

	len = strlen( argv[3] );
	if ( len == 0 ) {
		printf( "illegal file name\n" );
		exit(-1);
	}

	/* 判断是否可以使用该资源 */
	if ( get_access_right( inq_interval, retry_time, argv[3] ) == 1 ) {
		while ( count < 5 ) {
			printf( "pid: %ld process is occupying the resource,circle %d\n",
					(long)getpid(), count );
			count++;
			sleep(inq_interval);
		}

		release_right( argv[3] );
		return 0;
	} else {
		printf( "pid: %ld process cannot access the resource ... retry %d times\n", (long)getpid(), retry_time );
	}

	return 0;
}
