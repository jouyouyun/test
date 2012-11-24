#include "main.h"

int main(int argc,char *argv[])
{
	int ch;
	int opterr=0;	//不在输出错误信息//
	//目标参数初始化//
	struct threadpara tp;
	strcpy(tp.ip,"127.0.0.1");
	tp.minport=1;
	tp.maxport=65534;
	//默认线程数为10//
	int thread_num=10;

	while ((ch=getopt(argc,argv,"i:p:c:h"))!=-1)
	{
		switch (ch)
		{
			case 'h':
				help();
				return 0;
			case 'p':
				if(set_port(&tp,optarg)!=0)
					return 0;
				break;
			case 'i':
				strcpy(tp.ip,optarg);
				break;
			case 'c':
				thread_num=atoi(optarg);
				break;
			case '?':
				printf("不能识别的参数!\n输入参数-h查看帮助\n");
				return 0;
			default:
				printf("参数错误!\n");
				return 0;
		}
	}
	//默认使用10线程全连接扫描//
	multi_scan(tp,thread_num);
}


