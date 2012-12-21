/*
 * Snake control file
 */

#include "my_snake.h"
#include <time.h>
#include <unistd.h>

void game_start()
{
	srand( (int)time(NULL) );
	dir = rand() % 4 + 1;

	snake_head.x = rand() % width + 2;
	snake_head.y = rand() % length + 2;

	snake_len = 1;
	switch ( dir ) {
		case 1:
			draw_head( &snake_head );
			snake_body[0].x = snake_head.x;
			snake_body[0].y = snake_head.y + 1;
			draw_body( &snake_body[0] );
			break;
		case 2:
			draw_head( &snake_head );
			snake_body[0].x = snake_head.x;
			snake_body[0].y = snake_head.y - 1;
			draw_body( &snake_body[0] );
			break;
		case 3:
			draw_head( &snake_head );
			snake_body[0].y = snake_head.y;
			snake_body[0].x = snake_head.x - 1;
			draw_body( &snake_body[0] );
			break;
		case 4:
			draw_head( &snake_head );
			snake_body[0].y = snake_head.y;
			snake_body[0].x = snake_head.x + 1;
			draw_body( &snake_body[0] );
			break;
		default :
			break;
	}
}

void *snake_move( void *arg )
{
	int delay = 200;

	while (1) {
		clear_ch( &snake_head );
		switch ( dir ) {
			case 1:	// UP
				snake_head.y -= 1;
				draw_head( &snake_head );

				clear_ch( &snake_body[snake_len - 1] );
				
				update_body_pos();
				snake_body[0].x = snake_head.x;
				snake_body[0].y = snake_head.y + 1;

				update_body_ch();
				break;
			case 2:	// DOWN
				snake_head.y += 1;
				draw_head( &snake_head );

				clear_ch( &snake_body[snake_len - 1] );
				
				update_body_pos();
				snake_body[0].x = snake_head.x;
				snake_body[0].y = snake_head.y - 1;

				update_body_ch();
				break;
			case 3:	// RIGTH
				snake_head.x += 1;
				draw_head( &snake_head );

				clear_ch( &snake_body[snake_len - 1] );
				
				update_body_pos();
				snake_body[0].y = snake_head.y;
				snake_body[0].x = snake_head.x - 1;

				update_body_ch();
				break;
			case 4:	// LEFT
				snake_head.x -= 1;
				draw_head( &snake_head );

				clear_ch( &snake_body[snake_len - 1] );
				
				update_body_pos();
				snake_body[0].y = snake_head.y;
				snake_body[0].x = snake_head.x + 1;

				update_body_ch();
				break;
			default :
				break;
		}
		usleep( delay * 2 * 1000 );
	}

	pthread_exit(NULL);
}

void update_body_pos()
{
	int i;

	/* 更新蛇身坐标 */
	for ( i = snake_len - 1; i; i-- ) {
		snake_body[i].x = snake_body[i - 1].x;
		snake_body[i].y = snake_body[i - 1].y;
	}
}

void update_body_ch()
{
	int i;

	/* 重绘蛇身 */
	for ( i = 0; i < snake_len; i++ ) {
		draw_body( &snake_body[i] );
	}
}
