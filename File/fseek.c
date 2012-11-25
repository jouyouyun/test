/*
 *	test thread && fseek
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define MAX_BUF_SIZE 100

typedef struct test_thrd {
	int len;
	char str[MAX_BUF_SIZE];
	off_t start;
	FILE *fpread, *fpwrite;
} THRD;

void *fun_thrd( void *arg );

int main()
{
	int ret;
	THRD test;
	pthread_t thrd[2];

	if ( (test.fpread = fopen( "../test.txt", "r" )) == NULL ) {
		fprintf( stderr, "open read file err: %s\n", strerror(errno) );
		return -1;
	}

	if ( (test.fpwrite = fopen( "/tmp/tmp", "w" )) == NULL ) {
		fprintf( stderr, "open file err: %s\n", strerror(errno) );
		fclose(test.fpread);
		return -1;
	}

	test.start = 0;
	test.len = 250;
	ret = pthread_create( &thrd[0], 0, fun_thrd, &test );
	if ( ret != 0 ) {
		fprintf( stderr, "thread 0 create err: %s\n", strerror(errno) );
		fclose(test.fpread);
		fclose(test.fpwrite);
		return -1;
	}
	pthread_join( thrd[0], NULL );

	test.start += test.len;
	test.len = 1024;
	ret = pthread_create( &thrd[1], 0, fun_thrd, &test );
	if ( ret != 0 ) {
		fprintf( stderr, "thread 1 create err: %s\n", strerror(errno) );
		fclose(test.fpread);
		fclose(test.fpwrite);
		return -1;
	}

	pthread_join( thrd[1], NULL );
	fclose(test.fpread);
	fclose(test.fpwrite);

	return 0;
}

void *fun_thrd( void *arg )
{
	int len;
	THRD *test = ( THRD* ) arg;

	fseek( test->fpread, test->start, SEEK_SET );
	fseek( test->fpwrite, test->start, SEEK_SET );
	while ( (!feof(test->fpread)) && test->len > 0 ) {
		if ( test->len <= MAX_BUF_SIZE ) {
			len = fread( test->str, sizeof(char), test->len, test->fpread );
		} else {
			len = fread( test->str, sizeof(char), MAX_BUF_SIZE, test->fpread );
		}
		if ( len == -1 ) {
			fprintf( stderr, "write file err: %s\n", strerror(errno) );
			pthread_exit(NULL);
			break;
		}

		if ( fwrite( test->str, sizeof(char), len, test->fpwrite ) == -1 ) {
			fprintf( stderr, "write file err: %s\n", strerror(errno) );
			pthread_exit(NULL);
			break;
		}
		test->start += len;
		test->len -= len;
	}

	pthread_exit(NULL);
}
