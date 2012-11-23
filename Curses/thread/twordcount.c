/*
 *	count
 */

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

typedef struct arg_set {
	char *fname;
	int count;
} ARG;

void *count( void *arg );

ARG *mailbox;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  flag = PTHREAD_COND_INITIALIZER;

int main( int argc, char *argv[] )
{
	pthread_t t1, t2;
	ARG arg1, arg2;
	int ret;
	int reports_in = 0;
	int total = 0;

	if ( argc != 3 ) {
		fprintf( stderr, "Usage: %s file1 file2\n", argv[0] );
		return -1;
	}

	pthread_mutex_lock( &lock );
	
	arg1.fname = argv[1];
	arg1.count = 0;
	ret = pthread_create( &t1, 0, count, (void*)&arg1 );
	if ( ret != 0 ) {
		fprintf( stderr, "create thread 1 err: %s\n", strerror(errno) );
		return -1;
	}

	arg2.fname = argv[2];
	arg2.count = 0;
	ret = pthread_create( &t2, 0, count, (void*)&arg2 );
	if ( ret != 0 ) {
		fprintf( stderr, "create thread 1 err: %s\n", strerror(errno) );
		return -1;
	}

	while ( reports_in < 2 ) {
		fprintf( stdout, "MAIN: waiting for flag to go up\n" );
		pthread_cond_wait( &flag, &lock );
		printf( "MAIN: Wow! flag was raised, I have the lock\n" );
		printf( "%7d: %s\n", mailbox->count, mailbox->fname );
		total += mailbox->count;

		if ( mailbox == &arg1 ) {
			pthread_join( t1, NULL );
		}

		if ( mailbox == &arg2 ) {
			pthread_join( t2, NULL );
		}

		mailbox = NULL;
		pthread_cond_signal( &flag );
		reports_in++;
	}

	printf( "%7d: total\n", total );

	return 0;
}

void *count( void *arg )
{
	ARG *args = (ARG*)arg;
	FILE *fp;
	int c, prevc = '\0';

	if ( ( fp = fopen( args->fname, "r" )) == NULL ) {
		fprintf( stderr, "open %s: %s\n", args->fname, strerror(errno) );
		pthread_exit(NULL);
	}

	while ( ( c = getc(fp) ) != EOF ) {
		if ( !isalnum(c) && isalnum(prevc) ) {
			args->count++;
		}

		prevc = c;
	}
	fclose(fp);

	printf( "COUNT: waiting to get lock\n" );
	pthread_mutex_lock(&lock);
	printf( "COUNT: have lock, storing data\n" );
	if ( mailbox != NULL ) {
		pthread_cond_wait( &flag, &lock );
	}
	mailbox = args;

	printf( "COUNT: raising flag\n" );
	pthread_cond_signal( &flag );
	printf( "COUNT: unlocking box\n" );
	pthread_mutex_unlock( &lock );

	pthread_exit(NULL);
}
