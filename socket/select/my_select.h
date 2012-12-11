/*
 * select 多路复用
 */

#ifndef __MY_SELECT_H__
#define __MY_SELECT_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUF_LEN 80
#define SERV_PORT 8000
#define MAX_CONNECT 20

int setaddr( struct sockaddr_in *addr, struct hostent *host, char *dest );
int cmp( const void *sp1, const void *sp2 );

#endif
