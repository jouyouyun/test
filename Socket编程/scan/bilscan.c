#include "main.h"
//处理输入命令,设置ip和检测端口//
int threadpara_detection(struct threadpara tp)
{
	if(tp.ip==NULL)
	{
		printf("ip参数不完整!\n");
		return -1;
	}
	//检测端口的设置,大于或等于1,起始小于最大//
	if((tp.minport>=1)&&(tp.minport<tp.maxport))
	{
		//最大不能超过65534//
		if(tp.maxport<=65534)
		{
			return 0;
		}
	}
	printf("端口设置错误!范围在1-65534之间\n");
	return -2;
}
//处理命令,端口设置函数//
int set_port(struct threadpara *tp,char *ch)
{
	char *p;
	//如果没有'-'则默认从1到输入值//
	if(strchr(ch,'-')==0)
	{
		tp->minport=1;
		tp->maxport=atoi(ch);
	}
	//否则,分别赋值给起始小于最大//
	else
	{
		p=strtok(ch,"-");
		tp->minport=atoi(p);
		p=strtok(NULL,"-");
		tp->maxport=atoi(p);
	}
	return 0;
}
