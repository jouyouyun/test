/*
 * role bomb moving
 */

#include "my_curses.h"
#include <time.h>
#include <unistd.h>

POS *role_tmp;
pthread_mutex_t mutex;

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

/*
void *role_moving( void *arg )
{
	POS *role = (POS*)arg;

	while (1) {
		if ( role->dir != 0 ) {
			role->col += role->dir;
			draw_role( role->row, role->col );
			clear_ch( role->row, role->col - role->dir );
			role->dir = 0;
		}
		usleep( 200 * 1000 );
	}

	pthread_exit(NULL);
}
*/

void *bomb_moving( void *arg )
{
	int i;
	int delay = 200;
	POS bomb[bomb_num / 2];

	pthread_mutex_lock( &mutex );
	for ( i = 0; i < bomb_num / 2; i++ ) {
		genrate_bomb( &bomb[i] );
	}
	pthread_mutex_unlock( &mutex );

	while (1) {
		for ( i = 0; i < bomb_num; i++ ) {
			if ( game_over( role_tmp, &bomb[i]) ) {
				quit_flag = 1;
				pthread_exit( NULL );
			}

			if ( bomb_over(&bomb[i]) ) {
				clear_ch( bomb[i].row, bomb[i].col );
				genrate_bomb( &bomb[i] );
			}

			if ( bomb[i].dir == 1 ) {
				bomb[i].row += bomb[i].dir;
				draw_bomb( bomb[i].row, bomb[i].col );
				clear_ch( bomb[i].row - bomb[i].dir, bomb[i].col );
			}
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
