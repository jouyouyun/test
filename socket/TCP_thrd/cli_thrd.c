/*
 *	TCP pthread client
 */

#include "../my_tcp.h"
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

void *cli_send( void *arg );

int main( int argc, char *argv[] )
{
	int ret, cli_fd;
	pthread_t thrd_send;
	struct sockaddr_in ser_adddr;
	socklen_t addr_len = sizeof(struct sockaddr_in);

	if ( argc != 2 ) {
		fprintf( stdout, "Usage: %s Server IP\n", argv[0] );
		exit(-1);
	}

	cli_fd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( cli_fd == -1 ) {
		perror( "socket cli_fd create err!" );
		exit(-1);
	}

	/* 填充 ser_adddr 结构体 */
	bzero( &ser_adddr, sizeof(struct sockaddr_in) );
	ser_adddr.sin_family = AF_INET;
	ser_adddr.sin_port = htons(PORT);
	ser_adddr.sin_addr.s_addr = inet_addr(argv[1]);

	/* 连接服务器 */
	ret = connect( cli_fd, (struct sockaddr*)&ser_adddr, addr_len );
	if ( ret == -1 ) {
		perror( "connect server err!" );
		close(cli_fd);
		exit(-1);
	}

	ret = pthread_create( &thrd_send, 0, cli_send, (void*)cli_fd );
	if ( ret != 0 ) {
		perror( "thrd_send create err!" );
		close(cli_fd);
		exit(-1);
	}

	pthread_join(thrd_send, NULL);

	close(cli_fd);
	return 0;
}

void *cli_send( void *arg )
{
	char buffer[MAX_BUF_SIZE];
	int len;
	int cli_fd = (int)arg;

	while (1) {
		bzero( buffer, MAX_BUF_SIZE );

		fprintf( stdout, "Please Enter Masseges: \n" );
		fgets( buffer, MAX_BUF_SIZE, stdin );
		fflush(stdin);

		len = send( cli_fd, buffer, strlen(buffer) + 1, 0);
		if ( len == -1 ) {
			perror( "send msg err!" );
			break;
		}
		
		if ( strncmp( buffer, "quit", 4) == 0 ) {
			fprintf( stdout, "%s", buffer );
			break;
		}
		
		sleep(2);
		bzero( buffer, MAX_BUF_SIZE );
		len = recv( cli_fd, buffer, MAX_BUF_SIZE, 0);
		if ( len == -1 ) {
			perror( "recv msg err!" );
			break;
		}
		fprintf( stdout, "recv msg: %s", buffer );
	}

	pthread_exit(NULL);
}
