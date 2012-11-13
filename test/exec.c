#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUF_SIZE 1024

int main( int argc, char *argv[] )
{
	int fd, ret;
	//char buffer[MAX_BUF_SIZE]; 
	
	if ( argc != 2 ) {
		fprintf( stderr, "Usage: %s Dir\n", argv[0] );
		exit(-1);
	}
	
	fd = open( "tmp", O_CREAT | O_RDWR, 0666 );
	if ( fd == -1 ) {
		fprintf( stderr, "open file err: %s\n", strerror(errno) );
		exit(-1);
	}
	
	fprintf( stdout, "dup2 errsdfdsfsfs\n" );
	if ( dup2( fd, STDOUT_FILENO ) == -1 ) {
		fprintf( stderr, "dup2 err: %s\n", strerror(errno) );
		close(fd);
		exit(-1);
	}
	fprintf( stdout, "dup2 errsdfdsfsfs\n" );
	if ( execl( "/bin/ls", "ls", "-l", argv[1], NULL ) == -1 ) {
		fprintf( stderr, "execl err: %s\n", strerror(errno) );
		close(fd);
		exit(-1);
	}
	
	close(fd);
	
	return 0;
}
