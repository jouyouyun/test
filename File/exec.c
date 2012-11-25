#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TTY_SIZE 32
#define MAX_BUF_SIZE 1024

int main( int argc, char *argv[] )
{
	FILE *fp;
	char tty[TTY_SIZE];
	//char buffer[MAX_BUF_SIZE]; 
	
	if ( argc != 2 ) {
		fprintf( stderr, "Usage: %s Dir\n", argv[0] );
		exit(-1);
	}

	if ( ttyname_r( fileno(stdout), tty, sizeof(tty) ) != 0 ) {
		fprintf( stderr, "ttyname_r err: %s\n", strerror(errno) );
		exit(-1);
	}
	fprintf( stdout, "%s\n", tty );
	
	fp = freopen( "tmp", "w", stdout );
	if ( fp == NULL ) {
		fprintf( stderr, "open file err: %s\n", strerror(errno) );
		exit(-1);
	}
	
	/*
	fprintf( stdout, "dup2 errsdfdsfsfs\n" );
	if ( dup2( fd, STDOUT_FILENO ) == -1 ) {
		fprintf( stderr, "dup2 err: %s\n", strerror(errno) );
		close(fd);
		exit(-1);
	}
	fprintf( stdout, "dup2 errsdfdsfsfs\n" );
	*/
	if ( execl( "/bin/ls", "ls", "-l", argv[1], NULL ) == -1 ) {
		fprintf( stderr, "execl err: %s\n", strerror(errno) );
		fclose(fp);
		exit(-1);
	}
	
	/*
	if ( fclose(fp) != 0 ) {
		fprintf( stderr, "close err: %s\n", strerror(errno) );
		return -1;
	}
	*/

	/* 输出到控制台 */
	fp = freopen( tty, "w", stdout );
	if ( fp == NULL ) {
		fprintf( stderr, "open file err: %s\n", strerror(errno) );
		exit(-1);
	}
	fprintf( stdout, "errsdfdsfsfs\n" );
	fprintf( stderr, "errsdfdsfsfs\n" );
	
	return 0;
}
