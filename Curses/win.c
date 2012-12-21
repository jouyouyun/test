/*
 * 视窗
 */

#include "my_curses.h"
#include <unistd.h>

int
main( int argc, char *argv[] )
{
	WINDOW *win;

	init_curses();
	box(stdscr, ACS_VLINE, ACS_HLINE );
	mvaddstr( LINES / 2 - 5, COLS / 2 - 5, "hello world" );
	refresh();

	sleep(1);
	win = newwin(4, 30, LINES / 2 - 3, COLS / 2 - 15 );
	box(win, ACS_VLINE, ACS_HLINE );
	mvwaddstr( win, 1, 2, "hello world!!!" );
	touchwin(win);
	wrefresh(win);

	getch();
	wclear(win);
	touchwin(stdscr);
	sleep(5);

	endwin();
	return 0;
}
