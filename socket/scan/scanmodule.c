#include "main.h"
#include "scanmodule.h"

void *scan(void * tp_l)
{
	//将传入的地址强制转换//
	struct threadpara *tp=(struct threadpara *)tp_l;
	/*//调试用,看ip和端口的设置是否有错误//
	printf("%s,%d,%d\n",tp->ip,tp->minport,tp->maxport);
	*/
	int net;	//判断套接字是否错误//
	int i=0;
	int err;	//判断socket连线建立是否错误//
	for(i=tp->minport;i<=tp->maxport;i++)
	{
		struct sockaddr_in clientaddr;	//ip信息//
		clientaddr.sin_family=AF_INET;
		clientaddr.sin_addr.s_addr=inet_addr(tp->ip);	//ip地址转换
		clientaddr.sin_port=htons(i);	//端口地址转换//
		net=socket(AF_INET,SOCK_STREAM,0);	//创建套接字//
		if(net<0)
		{
			printf("套接字创建失败!\n");
			return 0;
		}
		//建立socket连线//
		 err=connect(net,(struct sockaddr *)&clientaddr,
				 sizeof(clientaddr));
		 if(err<0)
		 {
			 //printf("Port:%5d | Status:closed!!!\n", i);
			 close(net);
			 continue;
		 }
		 else
		 //显示监听端口的是什么服务//
		 {
		 	 struct servent * sptr;
			 if((sptr=getservbyport(htons(i),"tcp"))!=NULL)
			 {
			 	 printf("Port:%5d | Server: %s | Status: open!!\n",
			 	 i,sptr->s_name);
		 	 }
		 	 else
			 	 printf("Port:%5d | Status: open!!!\n",i); 
		 }
		 //关闭socket//
	 	 close(net);
	}
	//在这里释放前面申请用于保存ip和端口的结构体空间//
	free(tp);
	pthread_exit(NULL);
}
