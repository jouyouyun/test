/*
 * main
 */

#include "my_curses.h"

int
main( int argc, char *argv[] )
{
	int ret, ch;
	int cnt = 0;	/* 暂停后恢复 */

	POS role, bomb;
	pthread_t thrd_bomb;

	init_curses();
	quit_flag = 0;
	box( stdscr, ACS_VLINE, ACS_HLINE );

	/* get bomb_num */
	move( 1, COLS - 2 );
	getyx( stdscr, bomb.row, bomb.col );	/* 获取当前坐标 */
	bomb_num = bomb.col;

	genrate_bomb( &bomb );

	move( LINES - 2, COLS / 2 );
	getyx( stdscr, role.row, role.col );
	role.dir = 0;	/* 方向 */
	draw_role( role.row, role.col );

	/* 创建 bomb 线程 */
	ret = pthread_create( &thrd_bomb, NULL, bomb_moving, &bomb );
	if ( ret != 0 ) {
		perror( "thrd_bomb create err" );
		exit(-1);
	}
	
	while (1) {
		if ( !quit_flag ) {
			ch = getch();
		} else {
			ch = 27;	/* ESC */
		}

		switch( ch ) {
			case KEY_LEFT:
				role.dir = -1;
				role_move( &role );
				break;
			case KEY_RIGHT:
				role.dir = 1;
				role_move( &role );
				break;
			case 27:	/* ESC */
				quit_flag = 1;
				break;
			case ' ':	/* 暂停 */
				if ( cnt ) {
					bomb.dir = 1;
					cnt = 0;
				} else {
					bomb.dir = 0;
					cnt = 1;
				}
			default:
				break;
		}

		if ( quit_flag ) {
			break;
		}
	}
	/* 取消线程 */
	pthread_cancel( thrd_bomb );
	endwin();

	return 0;
}
