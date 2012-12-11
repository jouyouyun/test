/*
 * client
 */

#include "my_select.h"

int main( int argc, char *argv[] )
{
	int sockfd, n;
	char *dest;
	char buf[MAX_BUF_LEN];
	struct hostent *host = NULL;
	struct sockaddr_in ser_addr;
	socklen_t addr_len = sizeof(struct sockaddr);

	if ( argc != 2 ) {
		fprintf( stderr, "Usage: %s Hostname/Server address\n", argv[0] );
		exit(-1);
	}

	if ( (sockfd = socket( AF_INET, SOCK_STREAM, 0 )) == -1 ) {
		fprintf( stderr, "socket err: %s\n", strerror(errno) );
		exit(-1);
	}

	dest = argv[1];
	memset( &ser_addr, 0, sizeof(struct sockaddr_in) );
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(SERV_PORT);
	if ( setaddr( &ser_addr, host, dest ) == -1 ) {
		close(sockfd);
		exit(-1);
	}

	if ( connect(sockfd, (struct sockaddr*)&ser_addr, 
				(size_t)addr_len) == -1 ) {
		fprintf( stderr, "connect err: %s\n", strerror(errno) );
		close(sockfd);
		exit(-1);
	}

	while ( fgets(buf, MAX_BUF_LEN, stdin) != NULL ) {
		write( sockfd, buf, strlen(buf) );

		memset( buf, 0, MAX_BUF_LEN );
		n = read( sockfd, buf, MAX_BUF_LEN );
		if ( n == 0 ) {
			fprintf( stdout, "The other side has closed!\n" );
		} else if ( n == -1 ) {
			fprintf( stderr, "read err: %s\n", strerror(errno) );
			break;
		} else {
			fprintf( stdout, "Recieved: %s\n", buf );
		}
		memset( buf, 0, MAX_BUF_LEN );
	}

	close(sockfd);
	return 0;
}

int setaddr( struct sockaddr_in *addr, struct hostent *host, char *dest )
{
	if ( addr == NULL || dest == NULL ) {
		fprintf( stderr, "setaddr arguments err\n" );
		return -1;
	}

	if ( inet_addr(dest) == INADDR_NONE ) {
		if ( (host = gethostbyname(dest)) == NULL ) {
			fprintf( stderr, "gethostbyname err: %s\n", strerror(errno) );
			return -1;
		}
		dest = host->h_name;
		memcpy( (char*)&addr->sin_addr, host->h_addr, host->h_length );
	} else {
		addr->sin_addr.s_addr = inet_addr(dest);
	}

	return 0;
}
