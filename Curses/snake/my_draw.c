/*
 * My drawing snake funs
 */

#include "my_snake.h"

void init_curses()
{
	/* 开启 curses 模式 */
	initscr();

	/* 
	 * 开启 cbreak 模式，除了DELETE\CTRL 等仍被视为特殊控制字元外
	 * 一切输入的字符将立刻被一一读取 
	 */
	cbreak();

	/*
	 * 用来决定当输入资料时
	 * 按下 RETURN 键是否被对应为 NEWLINE 字符
	 */
	nonl();

	/*
	 * echo() and noecho()
	 * 此函式用来控制从键盘输入字元时是否将字元显示在终端机上
	 */
	noecho();

	intrflush( stdscr, false );

	/*
	 * 当开启 keypad 後, 可以使用键盘上的一些特殊字符
	 * 如上下左右>等方向键
	 */
	keypad( stdscr, true );

	/* 将做清除萤幕的工作 */
	refresh();
}

void draw_head( SPOS *shead )
{
	if ( shead == NULL ) {
		return ;
	}

	mvwaddch( stdscr, shead->y, shead->x, '@' );
	/*
	switch (dir) {
		case 1:	// UP
			mvwaddch( stdscr, shead->y, shead->x, '^' );
			break;
		case 2:	// DOWN
			mvwaddch( stdscr, shead->y, shead->x, 'v' );
			break;
		case 3:	// RIGTH
			mvwaddch( stdscr, shead->y, shead->x, '>' );
			break;
		case 4:	// LEFT
			mvwaddch( stdscr, shead->y, shead->x, '<' );
			break;
		default :
			break;
	}
	*/
}

void draw_body( SPOS *point )
{
	if ( point == NULL ) {
		return;
	}
 
		mvwaddch( stdscr, point->y, point->x, '&' );
}

void draw_food( SPOS *point )
{
	if ( point == NULL ) {
		return;
	}

	mvwaddch( stdscr, point->y, point->x, '$' );
}

void clear_ch( SPOS *point )
{
	if ( point == NULL ) {
		return;
	}

	mvwaddch( stdscr, point->y, point->x, ' ' );
}

void get_size()
{
	wmove( stdscr, LINES - 3, COLS - 3 );
	getyx( stdscr, length, width );
}
