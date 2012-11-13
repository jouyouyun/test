/*
 *	UDP Server
 */

#include "upload.h"
#include <signal.h>
//#include <pthread.h>

/* 中断处理函数 */
void end_ser( int sig );

FILE *fp;
TEST1 finfo;

int main()
{
	int ret;
	int flag = 1;
	int n = 1 * 1024;
	//pthread_t thrd_recv, thrd_send;

	/* 创建 sockfd */
	if ( (finfo.sockfd = socket( AF_INET, SOCK_DGRAM, 0 )) == -1 ) {
		perror( "sockfd create err!" );
		exit(-1);
	}
	
	if ( setsockopt( finfo.sockfd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n) ) == -1 ) {
		fprintf( stderr, "setsockopt err: %s\n", strerror(errno) );
		close(finfo.sockfd);
		exit(-1);
	}

	/* 填充 addr 结构 */
	finfo.addr_len = sizeof(struct sockaddr_in);
	bzero( &finfo.addr, (size_t)finfo.addr_len );
	finfo.addr.sin_family = AF_INET;
	finfo.addr.sin_port = htons(PORT);
	finfo.addr.sin_addr.s_addr = htonl(INADDR_ANY);

	/* bind sockfd */
	if (bind(finfo.sockfd, (struct sockaddr*)&finfo.addr, sizeof(struct sockaddr_in)) == -1) {
		perror( "bind sockfd err!" );
		close(finfo.sockfd);
		exit(-1);
	}
	
	/* 处理中断 */
	signal(SIGINT, end_ser);
	while (1) {
		if (flag){
		fp = fopen( "tmp.txt", "a+" );
		if ( fp == NULL ) {
			fprintf( stderr, "open file err: %s\n", strerror(errno) );
			close(finfo.sockfd);
			exit(-1);
		}
		}
		bzero( finfo.buffer, MAX_BUF_SIZE );
		ret = recvfrom( finfo.sockfd, &finfo, sizeof(TEST1), 0, (struct sockaddr*)&finfo.addr, 
			&finfo.addr_len );	
		if ( ret == -1 ) {
			fprintf( stderr, "msg_recv sendto err: %s\n", strerror(errno) );
			break;
		}
		fprintf( stdout, "recv msg: %s\n", finfo.buffer );
		ret = fwrite( finfo.buffer, sizeof(char), (strlen(finfo.buffer)), fp );
		if ( ret == -1 ) {
			fprintf( stderr, "write file err: %s\n", strerror(errno) );
			break;
		}
		//fclose(fp);
		fprintf( stdout, "file ends!\n" );
		flag = 0;
	}

	close(finfo.sockfd);
	return 0;
}

void end_ser( int sig )
{
	fclose(fp);
	close(finfo.sockfd);
	fprintf( stdout, "end_ser!\n" );
	exit(-1);
}