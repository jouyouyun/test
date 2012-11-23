/*
 *	thread curses
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <pthread.h>

typedef struct propset {
	char *str;	/* the message */
	int row;	/* the row */
	int delay;	/* delay in time units */
	int dir;	/* +1 or -1 */
} PROPSET;

/* The code that run in each thread  */
void *animate( void *arg );
int setup( int nstrings, char *strings[], PROPSET props[] );

#define MAXMSG	10		/* limit to number of strings */
#define TUNIT	20000		/* timeunits in microseconds */

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int main( int argc, char *argv[] )
{
	int c;
	pthread_t thrds[MAXMSG];
	PROPSET props[MAXMSG];
	int num_msg;
	int i;

	if ( argc == 1 ) {
		printf( "Usage: %s string ..\n", argv[0] );
		exit(-1);
	}

	num_msg = setup( argc - 1, argv + 1, props );

	/* create all the threads */
	for ( i = 0; i < num_msg; i++ ) {
		if ( pthread_create( &thrds[i], 0, animate, &props[i] ) != 0 ) {
			fprintf( stderr, "create thread err: %s\n", strerror(errno) );
			endwin();
			exit(-1);
		}
	}

	/* process user input */
	while (1) {
		c = getch();

		if ( c == 'Q' )
			break;

		if ( c == ' ' ) {
			for ( i = 0; i < num_msg; i++ ) {
				props[i].dir = -props[i].dir;
			}
		}

		if ( c >= '0' && c <= '9' ) {
			i = c - '0';
			if ( i < num_msg )
				props[i].dir = -props[i].dir;
		}
	}

	/* canel all the threads */
	pthread_mutex_lock(&lock);
	for ( i = 0; i < num_msg; i++ ) {
		pthread_cancel( thrds[i] );
	}
	endwin();

	return 0;
}

int setup( int nstrings, char *strings[], PROPSET props[] )
{
	int num_msg = ( nstrings > MAXMSG ? MAXMSG : nstrings );
	int i;

	/* assign row and velocities to each string */
	srand( getpid() );

	for ( i = 0; i < num_msg; i++ ) {
		props[i].str = strings[i];
		props[i].row = i;
		props[i].delay = 1 + ( rand() % 15 );
		props[i].dir = ((rand() % 2) ? 1 : -1 );
	}

	/* set up curses */
	initscr();
	crmode();
	noecho();
	clear();

	mvprintw( LINES - 1, 0, "\'Q\' -- QUIT, \'0\' .. \'%d\' to bounce",
			num_msg - 1 );

	return num_msg;
}

void *animate( void *arg )
{
	PROPSET *info = (PROPSET*)arg;
	int len = strlen( info->str ) + 2;		/* +2 for padding */
	int col = rand() % ( COLS - len - 3 );	/* space for padding*/

	while (1) {
		usleep( info->delay * TUNIT );

		pthread_mutex_lock( &lock );	/* only one thread */
		move( info->row, col );
		addch( ' ' );
		addstr( info->str );
		addch( ' ' );
		move( LINES - 1, COLS - 1 );
		refresh();
		pthread_mutex_unlock( &lock );

		/* move item to next column and check for bouncing */
		col += info->dir;

		if ( col <= 0 && info->dir == -1 ) {
			info->dir = 1;
		} else if ( col + len >= COLS && info->dir == 1 ) {
			info->dir = -1;
		}
	}
}
