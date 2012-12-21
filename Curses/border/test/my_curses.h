/*
 *	My Curses
 */

#ifndef __MY_CURSES_H__
#define __MY_CURSES_H__

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <pthread.h>

typedef struct position {
	int dir;
	int row, col;
} POS;

#define MAX_BUF_SIZE 1024

int bomb_num;
int quit_flag;

/* init curses */
void init_curses();
int draw_role( int row, int col );
int draw_bomb( int row, int col );
int clear_ch( int row, int col );

void role_move( POS *role );
int bomb_over( POS *bomb );
void genrate_bomb( POS *bomb );
int game_over( POS *role, POS *bomb );

void *bomb_moving( void *arg );

#endif
