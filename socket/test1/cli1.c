 /*
 *	UDP upload client
 */

#include "upload.h" 

int main( int argc, char *argv[] )
{
	int ret;
	FILE *fp;
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
	memset( &finfo.addr, 0, sizeof( struct sockaddr_in) );
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
		bzero( finfo.file_dir, MAX_DIR_LEN );
		scanf( "%s", finfo.file_dir );
		fflush(stdin);
		
		fp = fopen( finfo.file_dir, "r" );
		if ( fp == NULL ) {
			fprintf( stderr, "open file err: %s\n", strerror(errno) );
			break;
		}
		
		bzero( finfo.buffer, MAX_BUF_SIZE );
		while ( (ret = fread( finfo.buffer, sizeof(char), MAX_BUF_SIZE, fp)) > 0 ) {
			ret = sendto( finfo.sockfd, &finfo, sizeof(TEST1), 0, (struct sockaddr*)&finfo.addr, 
				finfo.addr_len );
			if ( ret == -1 ) {
				fprintf( stderr, "msg_send sendto err: %s\n", strerror(errno) );
				break;
			}
			bzero( finfo.buffer, MAX_BUF_SIZE );
		}
		fprintf( stdout, "file ends!\n" );
		fclose(fp);
	}

	close(finfo.sockfd);
	return 0;
}