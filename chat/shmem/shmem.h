/*
 * 共享内存聊天示例
 */

#ifndef __SHMEM_H__
#define __SHMEM_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>

#define PROJID 0xFF
#define FILENM "shared-file"
#define MAX_BUF_LEN 256

#endif
