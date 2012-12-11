/*
 * HTTP GET Resqust
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define HTTP_GET "GET / HTTP/1.1\r\nHost: %s\r\nAccept: */*\r\n\r\n"

int main( int argc, char *argv[] )
{
	int sockfd, n = 0;
	struct hostent *host;
	struct sockaddr_in dest_addr;
	char *dest;
	char *p, *tmp;
	char httpget[512];
	char buf[1024];

	if ( argc != 2 ) {
		fprintf( stderr, "Usage: %s Hostname/IP address\n", argv[0] );
		exit(-1);
	}

	dest = argv[1];
	if ( (sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1 ) {
		fprintf( stderr, "socket err: %s\n", strerror(errno) );
		exit(-1);
	}

	memset( &dest_addr, 0, sizeof(struct sockaddr_in) );
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port  = htons(80);
	if ( inet_addr(dest) == INADDR_NONE ) {
		if ( (host = gethostbyname(dest)) == NULL ) {
			fprintf( stderr, "gethostbyname err: %s\n", strerror(errno) );
			close(sockfd);
			exit(-1);
		}
		dest = host->h_name;
		memcpy( (char*)&dest_addr.sin_addr, host->h_addr, host->h_length );
	} else {
		dest_addr.sin_addr.s_addr = inet_addr(dest);
	}

	if ( connect(sockfd, (struct sockaddr*)&dest_addr, 
				sizeof(dest_addr)) == -1 ) {
		fprintf( stderr, "connect err: %s\n", strerror(errno) );
		close(sockfd);
		exit(-1);
	}

	sprintf( httpget, HTTP_GET, argv[1] );
	if ( write(sockfd, httpget, strlen(httpget)) == -1 ) {
		fprintf( stderr, "write err: %s\n", strerror(errno) );
		close(sockfd);
		exit(-1);
	}

	memset( buf, 0, 1024 );
	n = read( sockfd, buf, 1024 );
	p = strstr( buf, "\r\n\r\n" );
	/* 备份，避免出现内存碎片 */
	tmp = (char*)malloc( strlen(p) * sizeof(char) );
	if ( tmp == NULL ) {
		fprintf( stderr, "malloc err: %s\n", strerror(errno) );
		close(sockfd);
		exit(-1);
	}
	memcpy( tmp, p + 1, strlen(p) - 1 );
	free(tmp);

	*p = '\0';
	fprintf( stdout, "n = %d, buf = %s\n", n, buf );

	close(sockfd);
	return 0;
}
