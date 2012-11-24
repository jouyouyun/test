#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define LEN sizeof(struct threadpara)

//用于保存目标ip和端口设置//
struct threadpara
{
	char ip[20];
	unsigned int minport;
	unsigned int maxport;
};
//处理输入命令,设置ip和检测端口//
int threadpara_detection(struct threadpara tp);
//扫描函数//
void *scan(void * tp);
//多线程启动函数//
void multi_scan(struct threadpara tp,int thread_num);
//处理命令,端口设置函数//
int set_port(struct threadpara *tp,char *ch);
//帮助//
void help(void);

