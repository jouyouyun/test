/*
 *	UDP_upload 头文件
 */

#ifndef __UPLOAD_H__
#define __UPLOAD_H__

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 65520		/* 端口 */
#define MAX_DIR_LEN  128	/* 目录最大长度 */
#define MAX_BUF_SIZE 1024	/* 最大缓冲区 */
/* 上传文件目录 */
#define UPLOAD_DIR  "../upload_tmp/"

typedef struct test1 {
	unsigned int sockfd;
	/* 用于读取文件内容 */
	char buffer[MAX_BUF_SIZE];
	/* IP info */
	socklen_t addr_len;
	struct sockaddr_in addr;
}TEST1;

#endif
