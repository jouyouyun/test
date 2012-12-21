/*
 * role bomb moving
 */

#include "my_curses.h"
#include <time.h>
#include <unistd.h>

POS *role_tmp;

void role_move( POS *role )
{
	if ( role == NULL ) {
		return;
	}

	role_tmp = role;
	if ( role->dir != 0 ) {
		role->col += role->dir;
		draw_role( role->row, role->col );
		clear_ch( role->row, role->col - role->dir );
		role->dir = 0;
	}
	usleep( 200 * 1000 );
}

void *bomb_moving( void *arg )
{
	int delay = 200;
	POS *bomb = (POS*)arg;

	while (1) {
		if ( game_over( role_tmp, bomb ) ) {
			quit_flag = 1;
		}

		if ( bomb_over(bomb) ) {
			clear_ch( bomb->row, bomb->col );
			genrate_bomb( bomb );
		}

		if ( bomb->dir == 1 ) {
			bomb->row += bomb->dir;
			draw_bomb( bomb->row, bomb->col );
			clear_ch( bomb->row - bomb->dir, bomb->col );
		}
		usleep( delay * 2 * 1000 );
	}

	pthread_exit(NULL);
}

void genrate_bomb( POS *bomb )
{
	if ( bomb == NULL )
		return;

	srand( (int)time(NULL) );
	bomb->col = rand() % bomb_num + 1;
	bomb->row = 1;
	bomb->dir = 1;	/* 方向，向下 */

	draw_bomb( bomb->row, bomb->col );
}

int game_over( POS *role, POS *bomb )
{
	if ( role == NULL || bomb == NULL ) {
		return 0;
	}

	return ( role->row == bomb->row && role->col == bomb->col );
}

int bomb_over( POS *bomb )
{
	if ( bomb == NULL ) {
		return 0;
	}

	return ( bomb->row == LINES - 2 );
}
