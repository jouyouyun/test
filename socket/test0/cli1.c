 /*
 *	UDP upload client
 */

#include "upload.h" 

int main( int argc, char *argv[] )
{
	int ret;
	//FILE *fp;
	TEST1 finfo;
	//pthread_t thrd_send;

	if ( argc != 2 ) {
		fprintf( stdout, "Usage: %s ser_ip\n", argv[0] );
		exit(-1);
	}

	/* create sockfd */
	if ( (finfo.sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 ) {
		perror( "sockfd create err!" );
		exit(-1);
	}

	/* 填充 addr 结构 */
	finfo.addr_len = sizeof( struct sockaddr_in );
	bzero( &finfo.addr, sizeof( struct sockaddr_in) );
	finfo.addr.sin_family = AF_INET;
	finfo.addr.sin_port = htons( PORT );
	/*
	 *	inet_aton() 函数把字符串型的IP转换为网络字节序(大端字节序)
	 */
	if ( (inet_aton(argv[1], &finfo.addr.sin_addr)) < 0 ) {
		fprintf(stderr, "IP Convert err: %s\n", strerror(errno) );
		close(finfo.sockfd);
		exit(-1);
	}
	
	while (1) {
		bzero( finfo.buffer, MAX_BUF_SIZE );
		fgets( finfo.buffer, MAX_BUF_SIZE, stdin );
		fflush(stdin);
		
		ret = sendto( finfo.sockfd, &finfo, sizeof(TEST1), 0, (struct sockaddr*)&finfo.addr, 
			finfo.addr_len );
		if ( ret == -1 ) {
			fprintf( stderr, "msg_send sendto err: %s\n", strerror(errno) );
			break;
		}
	}

	close(finfo.sockfd);
	return 0;
}