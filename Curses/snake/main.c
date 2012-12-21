/*
 * Snake main
 */

#include "my_snake.h"
#include <time.h>

int
main( int argc, char *argv[] )
{
	int ch;
	int ret;
	int dir_pre;
	int cnt = 0;
	pthread_t thrd;

	init_curses();
	box( stdscr, ACS_VLINE, ACS_HLINE );

	get_size();
	game_start();
	/*
	srand( (int)time(NULL) );
	dir = rand() % 4 + 1;
	snake_len = 5;
	snake_head.x = rand() % width + 2;
	snake_head.y = rand() % length + 2;
	*/

	ret = pthread_create( &thrd, NULL, snake_move, NULL );
	if ( ret != 0 ) {
		printw( "thrd create err" );
		endwin();
		exit(-1);
	}

	quit_flag = 0;
	while (1) {
		ch = getch();

		switch (ch) {
			case KEY_UP:
				dir = 1;
				break;
			case KEY_DOWN:
				dir = 2;
				break;
			case KEY_RIGHT:
				dir = 3;
				break;
			case KEY_LEFT:
				dir = 4;
				break;
			case 27:		/* ESC */
				quit_flag = 1;
				break;
			case ' ':
				if ( !cnt ) {
					dir_pre = dir;
					dir = 0;
				} else {
					dir = dir_pre;
				}
				break;
			default:
				break;
		}

		if ( quit_flag ) {
			break;
		}
	}
	pthread_cancel(thrd);
	endwin();

	return 0;
}
