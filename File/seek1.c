/*
 * Test fseek
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_BUF_LEN 1024
#define TMP "/tmp/test"

typedef struct args {
	off_t start;
	off_t len;
	unsigned int read_len;
	char first;
	char buffer[MAX_BUF_LEN];
} ARGS;

int read_file( char *fname );
int write_file( ARGS *args );

int main( int argc, char *argv[] )
{
	if ( argc != 2 ) {
		printf( "Usage: %s file\n", argv[0] );
		exit(-1);
	}

	if ( read_file( argv[1] ) == -1 ) {
		printf( "read_file err\n" );
		exit(-1);
	}

	return 0;
}

int read_file( char *fname )
{
	off_t ret, len;
	FILE *fp, *tmp;
	struct stat buf;
	ARGS arg;

	if ( fname == NULL ) {
		printf( "read_file arguments err\n" );
		return -1;
	}

	if ( stat( fname, &buf ) == -1 ) {
		perror( "stat err" );
		return -1;
	}

	fp = fopen( fname, "r" );
	if ( fp == NULL ) {
		perror( "read_file open err" );
		return -1;
	}

	tmp = fopen( TMP, "w" );
	if ( tmp == NULL ) {
		perror( "tmp open err" );
		fclose(fp);
		return -1;
	}
 
	len = buf.st_size / 4;
	printf( "len: %ld\n", (long)len );
	fseek( fp, len, SEEK_SET );
	memset( arg.buffer, 0, MAX_BUF_LEN );
	arg.read_len = fread( arg.buffer, sizeof(char), len, fp );
	if ( arg.read_len == -1 ) {
		perror( "read err" );
		fclose(fp);
		fclose(tmp);
		return -1;
	}

	fseek( tmp, len, SEEK_SET );
	ret = fwrite( arg.buffer, sizeof(char), len, tmp );
	if ( ret == -1 ) {
		perror( "write err" );
		fclose(fp);
		fclose(tmp);
		return -1;
	}
/*
	fseek( fp, 0, SEEK_SET );
	memset( arg.buffer, 0, MAX_BUF_LEN );
	arg.read_len = fread( arg.buffer, sizeof(char), len, fp );
	if ( arg.read_len == -1 ) {
		perror( "read err" );
		fclose(fp);
		fclose(tmp);
		return -1;
	}

	fseek( tmp, 0, SEEK_SET );
	ret = fwrite( arg.buffer, sizeof(char), len, tmp );
	if ( ret == -1 ) {
		perror( "write err" );
		fclose(fp);
		fclose(tmp);
		return -1;
	}
*/
	fseek( fp, 2 * len, SEEK_SET );
	memset( arg.buffer, 0, MAX_BUF_LEN );
	arg.read_len = fread( arg.buffer, sizeof(char), len, fp );
	if ( arg.read_len == -1 ) {
		perror( "read err" );
		fclose(fp);
		fclose(tmp);
		return -1;
	}

	fseek( tmp, 2 * len, SEEK_SET );
	ret = fwrite( arg.buffer, sizeof(char), len, tmp );
	if ( ret == -1 ) {
		perror( "write err" );
		fclose(fp);
		fclose(tmp);
		return -1;
	}

	fseek( fp, 3 * len, SEEK_SET );
	memset( arg.buffer, 0, MAX_BUF_LEN );
	arg.read_len = fread( arg.buffer, sizeof(char), len, fp );
	if ( arg.read_len == -1 ) {
		perror( "read err" );
		fclose(fp);
		fclose(tmp);
		return -1;
	}

	fseek( tmp, 3 * len, SEEK_SET );
	ret = fwrite( arg.buffer, sizeof(char), len, tmp );
	if ( ret == -1 ) {
		perror( "write err" );
		fclose(fp);
		fclose(tmp);
		return -1;
	}

	printf( "len: %ld\n", (long)len );
		fclose(fp);
		fclose(tmp);
	return 0;
}
