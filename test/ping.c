/*
 *	简单的 ping 程序
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>

/* 数据报长度 */
#define PACKET_SIZE 4 * 1024
/* 等待时间 */
#define MAX_WAIT_TIME 5
/* 数据的有效长度 */
#define DATA_LEN 56
/* ICMP 报头长度 */
#define ICMP_HEADER_LEN 8
/* IP 报头长度 */
#define IP_HEADER_LEN 20
/* 发送数据报次数 */
#define MAX_NO_PACKETS 5

int sockfd;
/* 存储目的地址，即 argv[1] */
char *dest;
/* 存放发送数据 */
char sendpacket[PACKET_SIZE];
/* 存放接收数据 */
char recvpacket[PACKET_SIZE];
/* 记录发送和接收次数 */
int nsend = 0, nreceived = 0;
/* 记录每次的往返时间 */
double temp_rtt[MAX_NO_PACKETS];
/* 记录每次的总时间 */
double all_time = 0;
/* 目的地址结构体 */
struct sockaddr_in dest_addr;
/* 存放源地址结构体 */
struct sockaddr_in from;
/* 接收数据报的当前时间 */
struct timeval tvrecv;

pid_t pid;

/* 中断统计信息 */
void statistics( int sig )
{
	double min = 0;
	double max = 0;
	double avg = 0;
	int i;

	min = max = temp_rtt[0];
	if ( nreceived > 0 ) {
		avg = all_time / nreceived;
	}

	for ( i = 0; i < nreceived; i++ ) {
		if ( temp_rtt[i] < min ) 
			min = temp_rtt[i];
		else if ( temp_rtt[i] > max )
			max = temp_rtt[i];
	}

	printf( "\n--------------------------Ping %s statistics ----------\n", 
			dest );
	printf( "%d packets transmitted, %d recvived, %d%% packet loss, time %.lf ms\n", 
		  nsend, nreceived, (nsend - nreceived)/(nsend * 100), all_time );
	printf( "rtt min/avg/max = %.3f/%.3f/%.3fms\n", min, avg, max );
	close( sockfd );
	exit(1);
}

/* 校验和算法 */
unsigned short cal_chksum( unsigned short *addr, int len )
{
	unsigned short cksum;
	unsigned int sum = 0;

	while ( len > 1 ) {
		sum += *addr++;
		len -= 2;
	}

	if ( len == 1 ) {
		sum += *(unsigned char*)addr;
	}
	/* add hign 16 to low 16 */
	sum = (sum >> 16) + (sum & 0xffff);
	/* add carry */
	sum += (sum >> 16);
	/* truncate to 16 bits */
	cksum = ~sum;

	return (cksum);
}

/* 
 * 设置 ICMP 报头
 * ICMP 报头必须包含：类型TYPE（8\0）、编码CODE（未使用）、校验和CHECKSUM
 * 长度为８位，８位和１６位，其余选项则随ICMP的功能不同而不同
 * 其他信息如： 标志符Identifier、顺序号Sequence NO
 * Ping命令只使用众多ICMP报文中的两种："请求回送'(ICMP_ECHO)和"请求回应'(ICMP_ECHOREPLY)
 * #define ICMP_ECHO   0
 * #define ICMP_ECHOREPLY  8
 */
int pack_icmp( int pack_no )
{
	int packsize;
	struct icmp *icmp;
	struct timeval *tval;

	icmp = (struct icmp*)sendpacket;
	/* ICMP 类型：请求回应 */
	icmp->icmp_type = ICMP_ECHO;
	/* 编码 */
	icmp->icmp_code = 0;
	/* 校验和 */
	icmp->icmp_cksum = 0;
	/* 顺序号 */
	icmp->icmp_seq = pack_no;
	/* 标志符 */
	icmp->icmp_id = pid;
	
	packsize = ICMP_HEADER_LEN + DATA_LEN;
	tval = (struct timeval*)icmp->icmp_data;
	gettimeofday(tval, NULL);
	icmp->icmp_cksum = cal_chksum( (unsigned short*)icmp, packsize );

	return packsize;
}

/* 发送数据报 */
void send_packet( int sockfd )
{
	int packsize;

	if ( nsend < MAX_NO_PACKETS ) {
		nsend++;
		packsize = pack_icmp(nsend);
		if ( (sendto(sockfd, sendpacket, packsize, 0, 
						(struct sockaddr*)&dest_addr, sizeof(dest_addr))) 
				< 0 ) {
			perror( "sendto error" );
		}
	}
}

/* 计算往返时间 */
void tv_sub( struct timeval *recvtime, struct timeval *sendtime )
{
	long sec  = recvtime->tv_sec - sendtime->tv_sec;
	long usec = recvtime->tv_usec - sendtime->tv_usec;

	if ( usec >= 0 ) {
		recvtime->tv_sec  = sec;
		recvtime->tv_usec = usec;
	} else {
		recvtime->tv_sec  = sec - 1;
		recvtime->tv_usec = -usec;
	}
}

/* 剥除 ICMP 报头 */
int unpack_icmp( char *buf, int len )
{
	int iphdrlen;	/* IP 报头长度 */
	struct ip *ip;
	struct icmp *icmp;
	struct timeval *tvsend;
	double rtt;

	ip = (struct ip*)buf;
	/* IP 报头长度 */
	iphdrlen = ip->ip_hl << 2;
	/* 指向 ICMP 报头的位置 */
	icmp = (struct icmp*)(buf + iphdrlen);
	/* ICMP_HEADER_LEN + DATA_LEN */
	len -= iphdrlen;

	/* ICMP 地址格式不正确 */
	if ( len < 8 ) {
		printf( "ICMP packet\'s length is less than 8\n" );
		return -1;
	}

	if ( (icmp->icmp_type == ICMP_ECHOREPLY) && (icmp->icmp_id == pid) ) {
		tvsend = (struct timeval*)icmp->icmp_data;
		tv_sub( &tvrecv, tvsend );
		rtt = tvrecv.tv_sec * 1000 + tvrecv.tv_usec / 1000;
		temp_rtt[nreceived] = rtt;
		all_time += rtt;
		printf( "%d bytes from %s: icmp_seq = %u ttl = %d time = %.1f ms\n",
				len, inet_ntoa(from.sin_addr), icmp->icmp_seq, ip->ip_ttl, rtt);
	}

	return 0;
}

/* 接收数据报 */
void recv_packet( int sockfd )
{
	int n, fromlen;

	fromlen = sizeof(from);
	if ( nreceived < nsend ) {
		if ( (n = recvfrom(sockfd, recvpacket, sizeof(recvpacket), 0, 
						(struct sockaddr*)&from, (socklen_t*)&fromlen)) < 0 ) {
			perror( "recvpacket error!" );
		}

		gettimeofday( &tvrecv, NULL );
		unpack_icmp(recvpacket, n);
		nreceived++;
	}
}

int main( int argc, char *argv[] )
{
	struct hostent *host;	/* 存储目的主机的信息 */

	if ( argc != 2 ) {
		printf( "Usage: %s Hostname/IP address\n", argv[0] );
		exit(-1);
	}
	dest = argv[1];

	if ( (sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1 ) {
		perror( "socket create error!" );
		exit(-1);
	}

	bzero( &dest_addr, sizeof(dest_addr) );
	dest_addr.sin_family = AF_INET;
	/* 如果输入的不是IP */
	if ( inet_addr(dest) == INADDR_NONE ) {
		/* 若输入的也不是主机名 */
		if ( (host = gethostbyname(dest)) == NULL ) {
			perror( "gethostbyname error!" );
			exit(-1);
		}

		/* 若输入的是主机名 */
		dest = host->h_name;
		memcpy( (char*)&dest_addr.sin_addr, host->h_addr, host->h_length);
	} else {
		dest_addr.sin_addr.s_addr = inet_addr(dest);
	}

	pid = getpid();
	/* inet_ntoa 函数将整型转换为字符 */
	printf( "PING %s(%s) %d(%d) bytes of data.\n", dest, 
			inet_ntoa(dest_addr.sin_addr), DATA_LEN, IP_HEADER_LEN + 
			ICMP_HEADER_LEN + DATA_LEN );
	/* 处理中断 */
	signal(SIGINT, statistics);
	while( nsend < MAX_NO_PACKETS ) {
		send_packet(sockfd);
		recv_packet(sockfd);
		sleep(1);
	}

	return 0;
}
