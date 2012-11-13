#include "main.h"
#include "multiscan.h"

void multi_scan (struct threadpara tp,int thread_num)
{
	struct theradnumber	//线程创建返回值结构体,用于回收返回的线程//
	{
		pthread_t theradid;	//线程id//
		struct threadnumber *next;
	};
	//创建线程,最大为100//
	if(thread_num<=0)
		thread_num=10;
	if(thread_num>100)
		thread_num=100;
	if(threadpara_detection(tp)!=0)
		return ;
	//将端口平均分给每个线程
	int count=(tp.maxport-tp.minport)/thread_num;
	int i;	//循环用//
	int temp;	//判断线程的创建//

	printf("目标ip:%s,端口%d-%d\t线程数:%d\n",
			tp.ip,tp.minport,tp.maxport,thread_num);
	printf("Now start scanning......\n");
	//ip和端口的结构体,用于传给线程//
	struct threadpara *s;
	//一个链表,用于等待线程返回//
	struct theradnumber *h_num,*p_num,*s_num;
	//创建链表//
	h_num=(struct theradnumber *)malloc(sizeof(struct theradnumber));
	h_num->next=NULL;
	p_num=h_num;
	//线程创建部分//
	for(i=0;i<thread_num;i++)
	{
		//在这里申请空间,调用后在线程中释放//
		s=(struct threadpara *)malloc(LEN);
		strcpy(s->ip,tp.ip);
		s->minport=tp.minport+count*i;
		s->maxport=s->minport+count-1;
		if(thread_num-i==1)
			s->maxport=tp.maxport;
		/*//调试用//
		printf("线程%d,端口%d-%d,节点%d\n",
			//i,s->minport,s->maxport,n);
		printf("%s,%d,%d\n",s->ip,s->minport,s->maxport);
		*/
		temp=pthread_create(&p_num->theradid,NULL,
					scan,(void *)s);
		if(temp<0)
			printf("进程创建错误!\n");
		//链表的处理//
		s_num=(struct theradnumber *)malloc(sizeof(struct theradnumber));
		p_num->next=s_num;
		s_num->next=NULL;
		p_num=s_num;
	}
	//等待所有的进程结束//
	p_num=h_num;
	for(i=0;i<thread_num;i++)
	{
		pthread_join(p_num->theradid,NULL);
		p_num=p_num->next;
	}
	//释放链表的内存,可能有内存泄漏的嫌疑//
	for(i=0;i<thread_num;i++)
	{
		s_num->next=h_num->next;
		free(h_num);
		h_num=s_num->next;
	}
	printf("The end!\n");
}
