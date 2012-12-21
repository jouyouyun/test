/*
 * hello box
 */

#include "my_curses.h"

int main( int argc, char *argv[] )
{
	init_curses();
	/* draw a box */
	box( stdscr, ACS_VLINE, ACS_HLINE );
	
	if(start_color() == OK) /*开启颜色*/
	{
		//init_pair(1, COLOR_RED, COLOR_GREEN); /*建立一个颜色对*/
		init_pair(1, COLOR_BLACK, COLOR_BLACK); /*建立一个颜色对*/
		attron(COLOR_PAIR(1));	/*开启字符输出颜色*/
		/* move the cursor to the center */
		move( LINES / 2, COLS / 2 - 5 );
		//waddstr( stdscr, "Hello World!" );
		hline( '_', 2 );
		vline( '|', 1 );
		attroff(COLOR_PAIR(1));	/*关闭颜色显示*/
	}
	
	//mvaddstr( LINES / 2, COLS / 2 - 3, "    " );
	getch();
	endwin();

	return 0;
}
