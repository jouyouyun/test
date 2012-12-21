/*
 * hello box
 */

#include "my_curses.h"

int main( int argc, char *argv[] )
{
	init_curses();
	/* draw a box */
	box( stdscr, ACS_VLINE, ACS_HLINE );
	/* move the cursor to the center */
	move( LINES / 2, COLS / 2 - 5 );
	waddstr( stdscr, "Hello World!" );

	getch();
	endwin();

	return 0;
}
