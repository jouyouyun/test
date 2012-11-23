/*
 *	thread curses
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *moving_msg( void *arg );

#define MESSAGE "hello"

int row;	/* current row */
int col;	/* current column */
int dir;	/* where we are going */
int delay;	/* delay between moves */

int main()
{
	int ndelay;	/* new delay */
	int c;
	pthread_t msg_thread;

	initscr();
	crmode();
	noecho();
	clear();

	row = 1;
	col = 10;
	addstr( "Help\n" );
	addstr( "\'Q\' -- Quit\n\'f\' -- speed fast\n\'s\' -- speed slow\n" );
	addstr( "Space -- Change direction\n" );
	refresh();

	row = 10;
	col = 0;
	dir = 1;
	delay = 200;	/* 200ms = 0.2 seconds */

	if ( (pthread_create( &msg_thread, 0, moving_msg, MESSAGE)) != 0 ) {
		fprintf( stderr, "thread create err: %s\n", strerror(errno) );
		endwin();
		exit(-1);
	}

	while (1) {
		ndelay = 0;
		c = getch();
		if ( c == 'Q' )
			break;

		if ( c == ' ' ) 
			dir = -dir;

		if  ( c == 'f' && delay > 2 )
			ndelay = delay / 2;

		if ( c == 's' )
			ndelay = delay * 2;

		if ( ndelay > 0 ) 
			delay = ndelay;
	}
	pthread_cancel( msg_thread );
	endwin();

	return 0;
}

void *moving_msg( void *arg )
{
	while (1) {
		usleep(delay * 1000 );
		move( row, col );	/* set cursor position */
		addstr( arg );		/* redo message */
		refresh();			/* and show it */

		/* move to next column and check for bouncing */
		col += dir;	/* move to new column */

		if ( col <= 0 && dir == -1 ) {
			dir = 1;
		} else if ( col + strlen(arg) >= COLS && dir == 1 ) {
			dir = -1;
		}
	}
}
