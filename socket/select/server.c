/*
 * Server
 */

#include "my_select.h"

int main( int argc, char *argv[] )
{
	int i, n, max, maxfd;
	int serfd, connfd, sockfd;
	int nready, client[MAX_CONNECT];
	fd_set rset, allset;
	char buf[MAX_BUF_LEN];
	char ipstr[INET_ADDRSTRLEN];
	socklen_t addr_len = sizeof( struct sockaddr_in);
	struct sockaddr_in cliaddr, seraddr;
	struct timeval tv;

	if ( (serfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
		fprintf( stderr, "serfd create err: %s\n", strerror(errno) );
		exit(-1);
	}

	memset( &seraddr, 0, sizeof(seraddr) );
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SERV_PORT);
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ( (bind( serfd, (struct sockaddr*)&seraddr, (size_t)addr_len)) == -1 ) {
		fprintf( stderr, "serfd bind err: %s\n", strerror(errno) );
		close(serfd);
		exit(-1);
	}

	if ( (listen( serfd, MAX_CONNECT )) == -1 ) {
		fprintf( stderr, "serfd listen err: %s\n", strerror(errno) );
		close(serfd);
		exit(-1);
	}

	maxfd = serfd;
	max = -1;
	for ( i = 0; i < MAX_CONNECT; i++ ) {
		client[i] = -1;
	}
	FD_ZERO(&allset);
	FD_SET( serfd, &allset );

	sockfd = -1;
	while (1) {
		rset = allset;
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		nready = select( maxfd + 1, &rset, NULL, NULL, &tv );
		if ( nready == -1 ) {
			fprintf( stderr, "select err: %s\n", strerror(errno) );
			break;
		}

		if ( FD_ISSET( serfd, &rset ) ) {
			connfd = accept( serfd, (struct sockaddr*)&cliaddr, &addr_len );
			if ( connfd == -1 ) {
				fprintf( stderr, "accept err: %s\n", strerror(errno) );
				break;
			}
			fprintf( stdout, "Received from %s at PORT %d\n", 
					inet_ntop( AF_INET, &cliaddr.sin_addr, ipstr, sizeof(ipstr)), 
					ntohs(cliaddr.sin_port) );

			for ( i = 0; i < MAX_CONNECT; i++ ) {
				if ( client[i] < 0 ) {
					client[i] = connfd;
					break;
				}
			}

			if ( i == MAX_CONNECT ) {
				fprintf( stderr, "Too many clients\n" );
				break;
			}

			FD_SET( connfd, &allset );
			if ( connfd > maxfd ) {
				maxfd = connfd;
			}

			if ( i > max ) {
				max = i;
			}

			if ( --nready == 0 ) {
				continue;
			}
		}

		for ( i = 0; i <= max; i++ ) {
			if ( (sockfd == client[i]) < 0 ) {
				continue;
			}

			if ( FD_ISSET( sockfd, &rset ) ) {
				if ( ( n = read( sockfd, buf, MAX_BUF_LEN ) ) > 0 ) {
					qsort( buf, n, sizeof(char), cmp );
					buf[n] = '\0';
					write( sockfd, buf, n );
				}

				if ( --nready == 0 ) { 
					break;
				}
			}
		}
	}

	close(serfd);
	close(connfd);
	return 0;
}

int cmp( const void *sp1, const void *sp2 )
{
	const char s1 = *(char*)sp1;
	const char s2 = *(char*)sp2;

	return ( s1 > s2 ? 1 : s1 < s2 ? -1 : 0 );
}
