/* My Curses funs */

#include "my_curses.h"
#include <errno.h>

void
init_curses()
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

/*
 * 把输入内容保存到文件：/tmp/tmp
 */

int
write_file ( char *buf )
{
	FILE *fp;
	int ret;

	if ( buf == NULL ) {
		fprintf( stderr, "write_file arguments\n" );
		return -1;
	}

	if ( new_flag == 0 ) {
		fp = fopen( "/tmp/tmp", "w" );
	} else if ( new_flag == 1 ) {
		fp = fopen( "/tmp/tmp", "a+" );
	}
	if ( fp == NULL ) {
		fprintf( stderr, "fopen err: %s\n", strerror(errno) );
		return -1;
	}

	ret = fwrite( buf, sizeof(char), strlen(buf), fp );
	if ( ret == -1 ) {
		fprintf( stderr, "fwrite err: %s\n", strerror(errno) );
		return -1;
	}

	fclose(fp);
	return 0;
}

/*
 * is buffer full
 */

inline int
is_full( char *buf )
{
	if ( buf == NULL ) {
		fprintf( stderr, "is_full arguments\n" );
		return -1;
	}

	return ( strlen(buf) == (MAX_BUF_SIZE - 1) );
}

/*
 * 帮助信息
 */
void
help()
{
	mvaddstr( LINES / 2 - 1, COLS / 2 - 2, "Help" );
	mvaddstr( LINES / 2, COLS / 2 - 4, "ESC -- 退出" );
	mvaddstr( LINES / 2 + 1, COLS / 2 - 4, "F2 -- 保存到：/tmp/tmp" );
}
