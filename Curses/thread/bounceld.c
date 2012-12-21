/*
 * bounceld 弾珠 左右移动
 * 采用 curses 图形库
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void help();
/* 线程处理函数 */
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
	pthread_t msg_thread;	/* 线程 ID */

	initscr();	/* 初始化屏幕 */
	crmode();
	noecho();
	clear();
	
	help();

	/* move the cursor to the center */
	move( LINES / 2, COLS / 2 - 2 );
	dir = 1;	/* 初始方向为右 */
	delay = 200;	/* 200ms = 0.2 seconds */

	/* 创建线程 */
	if ( (pthread_create( &msg_thread, 0, moving_msg, MESSAGE)) != 0 ) {
		fprintf( stderr, "thread create err: %s\n", strerror(errno) );
		endwin();
		exit(-1);
	}

	while (1) {
		ndelay = 0;
		c = getch();
		/* 退出 */
		if ( c == 'Q' )
			break;

		/* 反向 */
		if ( c == ' ' ) 
			dir = -dir;

		/* 加速 */
		if  ( c == 'f' && delay > 2 )
			ndelay = delay / 2;

		/* 减速 */
		if ( c == 's' )
			ndelay = delay * 2;

		if ( ndelay > 0 ) 
			delay = ndelay;
	}
	
	pthread_cancel( msg_thread );	/* 取消线程 */
	endwin();

	return 0;
}

void *moving_msg( void *arg )
{
	while (1) {
		usleep(delay * 1000 );
		/* 清理痕迹 */
		move( row, col - dir );	/* set cursor position */
		addstr( "     " );	/* redo message */
		/* 显示字符 */
		move( row, col );		/* set cursor position */
		addstr( arg );		/* redo message */
		refresh();			/* and show it */

		col += dir;	/* move to new column */

		/* 检查是否到达边界，然则反向 */
		if ( col <= 1 && dir == -1 ) {
			dir = 1;
		} else if ( col + strlen(arg) >= COLS - 1 && dir == 1 ) {
			dir = -1;
		}
	}
}

void help()
{
	row = 10;
	col = COLS / 2 - 2;
	addstr( "Help\n" );
	col = COLS / 2 - 5;
	addstr( "\'Q\' -- Quit\n\'f\' -- speed fast\n\'s\' -- speed slow\n" );
	addstr( "Space -- Change direction\n" );
	refresh();
	
	/* draw a box */
	box( stdscr, ACS_VLINE, ACS_HLINE );
}

/*
 * 屏幕局部清除
 * clrtobot()清除从当前光标位置到屏幕底端的所有内容
 * clrtoeol()清除屏幕上从当前光标位置到该行末尾的所有字符
 */
//clrtobot();
/* 删除光标左边的字符，并把光标右边余下的字符向左移动一个位置 */
//mvdelch( row, col );