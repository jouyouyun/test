/*
 *	select 函数服务器端
 */

#include "../my_tcp.h"
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_CONNET 5	/* 最大连接数 */
int main()
{
	char buffer[MAX_BUF_SIZE];
	int n, ret;
	int ser_fd, cli_fd, maxfd;
	fd_set fds, rets;
	struct timeval tv;
	socklen_t addr_len = sizeof( struct sockaddr_in);
	struct sockaddr_in ser_addr;

	if ( (ser_fd = socket( AF_INET, SOCK_STREAM, 0)) == -1 ) {
		perror( "ser_fd create err!" );
		exit(-1);
	}

	/* 缓冲区大小 */
	n = 5*1024;
	if ( setsockopt( ser_fd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n)) == -1 ) {
		perror( "setsockopt err!" );
		close(ser_fd);
		exit(-1);
	}

	bzero( &ser_addr, (size_t)addr_len );
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(PORT);
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ( bind(ser_fd, (struct sockaddr*)&ser_addr, addr_len) == -1 ) {
		perror( "bind err!" );
		close(ser_fd);
		exit(-1);
	}

	if ( listen( ser_fd, MAX_CONNET ) == -1 ) {
		perror( "listen err!" );
		close(ser_fd);
		exit(-1);
	}

	maxfd = ser_fd + 1;
	FD_ZERO(&fds);
	/* 添加文件描述符 */
	FD_SET(ser_fd, &fds);
	while (1) {
		rets = fds;
		/* 轮询时间 */
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		ret = select( maxfd, &rets, 0, 0, &tv );
		switch( ret ) {
			case -1:
				perror( "select err!" );
				close(ser_fd);
				exit(-1);
			case 0:
				break;	/* 继续轮询 */
			default:
				/* 测试 ser_fd 是否可读 */
				if ( FD_ISSET(ser_fd, &fds)) {
					cli_fd = accept( ser_fd, (struct sockaddr*)&ser_addr, 
							&addr_len );
					if  (cli_fd == -1 ) {
						perror( "accept err!" );
						close(ser_fd);
						exit(-1);
					}

					bzero( buffer, MAX_BUF_SIZE );
					ret = recv( cli_fd, buffer, MAX_BUF_SIZE, 0);
					if ( ret == -1 ) {
						perror( "recv msg err!" );
						close(ser_fd);
						close(cli_fd);
						exit(-1);
					} else if ( ret == 0 ) {
						printf( "cli_fd has been closed!\n" );
						close(cli_fd);
						close(cli_fd);
						exit(-1);
					}
					printf( "recv msg : %s\n", buffer );
				}
		}
	}

	close(ser_fd);
	close(cli_fd);

	return 0;
}
