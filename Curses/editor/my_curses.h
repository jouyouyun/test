/*
 *	My Curses
 */

#ifndef __MY_CURSES_H__
#define __MY_CURSES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#define StartX 1
#define StartY 1
#define MAX_BUF_SIZE 1024

/* init curses */
void init_curses();
inline int is_full( char *buf );
int write_file( char *buf );
void help();

int new_flag;	/* 为 0 则新建文本 */

#endif
