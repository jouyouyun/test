/*
 *	TCP 多线程通信
 */

#include "../my_tcp.h"
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

void *ser_recv( void *arg );
void *ser_send( void *arg );

/* flag = 1 退出服务器 */
static int flag = 0;

int main()
{
	int ret;
	int no = 1;
	int ser_fd, cli_fd;
	pthread_t thrd_recv, thrd_send;
	struct sockaddr_in ser_addr, cli_addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	if ( (ser_fd = (socket( AF_INET, SOCK_STREAM, 0))) == -1 ) {
		perror( "ser_fd create err!" );
		exit(-1);
	}
	
	/* 端口复用 */
	if ( setsockopt(ser_fd, SOL_SOCKET, SO_REUSEADDR, &no, sizeof(no)) == -1 )
	{
		perror( "setsockopt err" );
		close(ser_fd);
		exit(-1);
	}

	/* 填充 ser_addr */
	bzero( &ser_addr, sizeof(struct sockaddr_in) );
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(PORT);
	ser_addr.sin_addr.s_addr = htonl( INADDR_ANY );

	ret=bind(ser_fd, (struct sockaddr*)&ser_addr, sizeof(struct sockaddr_in));
	if ( ret == -1 ) {
		perror("bind port err!");
		close(ser_fd);
		exit(-1);
	}

	ret = listen( ser_fd, 5 );
	if ( ret == -1 ) {
		perror("listen port err!");
		close(ser_fd);
		exit(-1);
	}

	/*
	 *	接收客户端的请求，然后进行通信
	 */
	while (1) {
		cli_fd = accept(ser_fd, (struct sockaddr*)&cli_addr, &addrlen);
		if ( cli_fd == -1 ) {
			if ( errno == EINTR ) {
				continue;
			} else {
				perror( "accept client connect err!" );
				break;
			}
		}

		ret = pthread_create( &thrd_recv, 0, ser_recv, (void *)cli_fd );
		if ( ret != 0 ) {
			perror( "thrd_recv create err!" );
			break;
		}
		pthread_join( thrd_recv, NULL );
		if ( flag ) {
			break;
		}
	}

	close(ser_fd);
	close(cli_fd);
	return 0;
}

void *ser_recv( void *arg )
{
	int cli_fd = (int)arg;
	int len, i = 0;
	char buffer[MAX_BUF_SIZE];

	bzero( buffer, MAX_BUF_SIZE );
	while ( (len = recv(cli_fd, buffer, MAX_BUF_SIZE, 0)) > 0 ) {
		/* 退出 */
		if ( strncmp( buffer, "quit", 4) == 0 ) {
			fprintf( stdout, "%s", buffer );
			flag = 1;
			break;
		}
		fprintf( stdout, "Received Massege: %s", buffer );

		for ( i = 0; i < len; i++ ) {
			//小写转大写
			buffer[i] = toupper(buffer[i]);
		}

		if ( send( cli_fd, buffer, len, 0) == -1 ) {
			perror( "send msg err!" );
			break;
		}
		bzero( buffer, MAX_BUF_SIZE );
	}

	pthread_exit(NULL);
}
