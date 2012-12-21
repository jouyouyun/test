/*
 *	My Curses
 */

#ifndef __MY_CURSES_H__
#define __MY_CURSES_H__

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <pthread.h>

/* 定义字符位置 */
typedef struct position {
	int dir;
	int row, col;
} POS;

/* 界面框体的宽度 */
int bomb_num;
/* 退出标志 */
int quit_flag;

/* init curses */
void init_curses();
int draw_role( int row, int col );
int draw_bomb( int row, int col );
int clear_ch( int row, int col );

void role_move( POS *role );
int bomb_over( POS *bomb );
/* 随机产生 bomb */
void genrate_bomb( POS *bomb );
int game_over( POS *role, POS *bomb );

void *bomb_moving( void *arg );

#endif
