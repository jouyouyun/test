/*
 * Server
 */ 

#include "my_sock.h"

int main( int argc, char *argv[] )
{
	int ret;
	int n = 1 *1024;
	ARGS args;

	args.sockfd = socket( AF_INET, SOCK_DGRAM, 0 );
	if ( args.sockfd == -1 ) {
		perror( "create sock err" );
		exit(-1);
	}

	ret = setsockopt( args.sockfd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n) );
	if ( ret == -1 ) {
		perror( "setsockopt err" );
		close( args.sockfd );
		exit(-1);
	}

	args.addr_len = sizeof( struct sockaddr_in );
	memset( args.addr, 0, (sizeof)args.addr_len );
	args.addr.sin_family = AF_INET;
	args.addr.sin_port = htons( PORT );
	args.addr.sin_addr.s_addr = htonl( INADDR_ANY );

	ret = bind( args.sockfd, (struct sockaddr*)args.addr, (sizeof)args.addr_len );
	if ( ret == -1 ) {
		perror( "bind err" );
		close( args.sockfd );
	}

	signal( SIGINT, end_ser );

	while (1) {
		ret = msg_recv( &args );
		if ( ret == -1 ) {
			printf( "msg_recv err\n" );
			break;
		}

		ret = write_file( &args );
		if ( ret == -1 ) {
			printf( "write_file err" );
			break;
		}
	}

	close( args.sockfd );
	return 0;
}
