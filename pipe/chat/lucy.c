#include "name_fifo.h"

int main( int argc, char *argv[] )
{
	char buf[MAX_BUF_LEN];
	char read_fifo_name[] = "read-fifo";
	char write_fifo_name[] = "write-fifo";

	int write_fd, read_fd;
	int ret, len;

	ret = mkfifo( write_fifo_name, S_IRUSR | S_IWUSR );
	if ( ret == -1 ) {
		fprintf( stderr, "mkfifo err: %s\n", strerror(errno) );
		exit(-1);
	}

	write_fd = open( write_fifo_name, O_WRONLY );
	if ( write_fd == -1 ) {
		fprintf( stderr, "open write err: %s\n", strerror(errno) );
		exit(-1);
	}

	while ( (read_fd = open( read_fifo_name, O_RDONLY )) == -1 ) {
		sleep(1);
	}

	while (1) {
		printf( "Lucy: " );
		fgets( buf, MAX_BUF_LEN, stdin );
		buf[strlen(buf) - 1] = '\0';

		if ( strncmp( buf, "quit", 4 ) == 0 ) {
			close( write_fd );
			unlink( write_fifo_name );
			close(read_fd );
			exit(-1);
		}

		if ( (write(write_fd, buf, strlen(buf))) == -1 ) {
			fprintf( stderr, "write err: %s\n", strerror(errno) );
			close( write_fd );
			unlink( write_fifo_name );
			close(read_fd );
			exit(-1);
		}

		len = read( read_fd, buf, MAX_BUF_LEN );
		if ( len > 0 ) {
			buf[len] = '\0';
			printf( "Peter: %s\n", buf );
		}
	}

	return 0;
}
