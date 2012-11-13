/* test 1 */
#include <stdio.h>
#include <curses.h>

int main()
{
	initscr();
	clear();

	move( 10, 20 );
	addstr( "hello, world" );
	refresh();
	/* 输入任意字符结束 */
	getch();
	endwin();

	return 0;
}
