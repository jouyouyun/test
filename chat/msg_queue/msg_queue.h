/*
 * 消息队列聊天程序
 */

#ifndef __MSG_QUEUE_H__
#define __MSG_QUEUE_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define FILENM "shared-file"

#define PROJID 0xFF
#define SNDMSG 1
#define RCVMSG 2
#define MAX_BUF_LEN 256

typedef struct msgbuf {
	long mtype;
	char mtext[MAX_BUF_LEN];
} MSGBUF;

#endif
