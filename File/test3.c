/*
 *  同时打开一文件多次
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main( int argc, char *argv[] )
{
	int fd1, fd2;

	if ( (fd1 = open( "infile.txt", O_RDWR )) == -1 ) {
		fprintf( stderr, "fp1 open err: %s\n", strerror(errno) );
		exit(-1);
	}

	if ( (fd2 = open( "infile.txt", O_RDWR )) == -1 ) {
		fprintf( stderr, "fp2 open err: %s\n", strerror(errno) );
		close(fd1);
		exit(-1);
	}

	fprintf( stdout, "fp1: %d\tfp2: %d\n", fd1, fd2 );

	close(fd1);
	close(fd2);

	return 0;
}
