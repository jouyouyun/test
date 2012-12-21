/*
 *	My Curses
 */

#ifndef __MY_SNAKE_H__
#define __MY_SNAKE_H__

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <pthread.h>

#define MAX_SNAKE_LEN 20

typedef struct snake_pos {
	int x, y;
} SPOS;

int quit_flag;

int dir;
int snake_len;
int length, width;
SPOS snake_head;
SPOS snake_body[MAX_SNAKE_LEN];

/* init curses */
void init_curses();

void draw_head( SPOS *shead );
void draw_body( SPOS *sbody );
void draw_food( SPOS *sfood );
void clear_ch( SPOS *point );

void get_size();

void game_start();

void *snake_move( void *arg );
void update_body_pos();
void update_body_ch();

#endif
