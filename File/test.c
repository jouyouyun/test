#include "my_sock.h"

int main()
{
	int total = 1024;
	FILE *fp;

	if ( (fp = fopen("/tmp/test", "w")) == NULL ) {
		fprintf( stderr, "open err: %s\n", strerror(errno) );
		return -1;
	}

	fseek( fp, total, SEEK_SET );
	fwrite( "a", 1, 1, fp );

	fclose(fp);

	return 0;
}
