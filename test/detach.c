/*
 *	pthread_detach
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *func( void *arg )
{
	int i = 0;

	for ( i = 0; i < 5; i++ ) {
		printf( "%s ", (char*)arg );
	}
	printf( "\n" );
	pthread_exit(NULL);
}

int main()
{
	int ret, c;
	pthread_t thrd;
	char str[] = "hello world!";

	while (1) {
		printf( "Arch Linux!\n" );
		c = getchar();

		if ( c == 'Q' ) {
			pthread_cancel( thrd );
			break;
		}

		ret = pthread_create( &thrd, 0, func, str );
		if ( ret != 0 ) {
			perror( "create thrd err" );
			break;
		}
		pthread_detach( thrd );
	}

	return 0;
}
