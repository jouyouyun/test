/*
 * main
 */

#include "my_curses.h"
//#include <math.h>

int
main( int argc, char *argv[] )
{
	int ret, ch;
	int cnt = 0;	/* 暂停后恢复 */
	//int pause_flag = 0;

	POS role, bomb;
	pthread_t thrd_bomb;
	//pthread_t thrd_role, thrd_bomb;

	init_curses();
	box( stdscr, ACS_VLINE, ACS_HLINE );
	quit_flag = 0;

	/* get bomb_num */
	move( 1, COLS - 1 );
	getyx( stdscr, bomb.row, bomb.col );
	bomb_num = bomb.col;

	//move( 1, bomb.col );
	//getyx( stdscr, bomb.row, bomb.col );
	//bomb.row = 1;
	//bomb.col = COLS / 2 -5;
	//bomb.col = rand() % (COLS - 2 ) + 1;

	move( LINES - 2, COLS / 2 );
	getyx( stdscr, role.row, role.col );
	role.dir = 0;	/* 方向 */
	draw_role( role.row, role.col );
	//role.row = LINES - 2;
	//role.col = COLS / 2;

	/*
	ret = pthread_create( &thrd_role, NULL, role_moving, &role );
	if ( ret != 0 ) {
		perror( "thrd_role create err" );
		exit(-1);
	}
	*/

	ret = pthread_create( &thrd_bomb, NULL, bomb_moving, NULL );
	if ( ret != 0 ) {
		perror( "thrd_bomb create err" );
		//pthread_cancel( thrd_role );
		exit(-1);
	}
	
	while (1) {
		ch = getch();
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
			case ' ':
				if ( cnt ) {
					//pause_flag = 0;	/* 继续 */
					bomb.dir = 1;
					cnt = 0;
				} else {
					//pause_flag = 1;	/* 暂停 */
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
	//pthread_cancel( thrd_role );
	pthread_cancel( thrd_bomb );
	endwin();

	return 0;
}
