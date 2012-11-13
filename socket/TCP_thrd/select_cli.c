/*
 *	select 函数测试客户端
 */

#include "../my_tcp.h"
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void *cli_send( void *arg )
{
	int ret;
	int cli_fd = (int)arg;
	char buffer[MAX_BUF_SIZE];

	while ( fgets( buffer, MAX_BUF_SIZE, stdin) != NULL ) {
		ret = send( cli_fd, buffer, MAX_BUF_SIZE, 0 );
		if ( ret == -1 ) {
			perror( "send msg err!" );
			break;
		}

		sleep(1);
		bzero( buffer, MAX_BUF_SIZE );
		ret = recv( cli_fd, buffer, MAX_BUF_SIZE, 0 );
		if ( ret == -1 ) {
			perror( "recv msg err!" );
			break;
		} else if ( ret == 0 ) {
			printf( "cli_fd has been closed!\n" );
			break;
		}
		printf( "Recv Mag: %s\n", buffer );
		bzero( buffer, MAX_BUF_SIZE );
	}

	pthread_exit(NULL);
}

int main( int argc, char *argv[] )
{
	int ret;
	int cli_fd;
	pthread_t thrd_send;
	struct sockaddr_in ser_addr;
	socklen_t addr_len = sizeof( struct sockaddr_in );

	if ( argc != 2 ) {
		printf( "Usage: %s Server IP\n", argv[0] );
		exit(-1);
	}

	if ( (cli_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
		perror( "cli_fd create err!" );
		exit(-1);
	}

	bzero( &ser_addr, (size_t)addr_len );
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(PORT);
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if ( (connect( cli_fd, (struct sockaddr*)&ser_addr, addr_len)) == -1 ) {
		perror( "connect Server err!" );
		close(cli_fd);
		exit(-1);
	}

	ret = pthread_create( &thrd_send, 0, cli_send, (void*)cli_fd);
	if ( ret != 0 ) {
		perror( "thrd_send create err!\n" );
		close(cli_fd);
		exit(-1);
	}

	pthread_join(thrd_send, NULL);
	close(cli_fd);
	
	return 0;
}
