/*
 * My UDP Upload
 */

#ifndef __MY_SOCK_H__
#define __MY_SOCK_H__

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>

#define TMP "/tmp/tmp"
#define MAX_BUF_SIZE 1024
#define PATH_LEN	128
#define THRD_NUM	4	/* 线程数 */

typedef struct thrd_arg {
	short int first_flag;
	int read_len;
	off_t start;
	off_t len;
	char path[PATH_LEN];
	char buffer[MAX_BUF_SIZE];
} ARGS;

void *thrd_read( void *arg );
int read_file( char *fname );
int write_file( ARGS *args ); 

#endif
