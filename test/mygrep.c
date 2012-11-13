#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN	80

int main( int argc, char **argv )
{
	char buf[MAX_LINE_LEN];
	FILE *fp;
	int lineID = 0;

	if ( argc != 3 ) {
		printf( "Usages: %s searchkey filename\n", argv[0] );
		exit(-1);
	}

	if ( ( fp = fopen( argv[2], "r" ) ) == NULL ) {
		perror( "open file err" );
		exit( -1 );
	}

	while ( !feof(fp) ) {
		if ( !fgets( buf, MAX_LINE_LEN, fp) ) {
			//perror( "fgets err" );
			if ( fp != NULL ) {
				fclose(fp);
			}
			exit(-1);
		}
		//printf( "%s  %d\n", argv[1], strlen(argv[1]) );
		++lineID;

		if ( strstr( buf, argv[1] ) ) {
			printf( "line %d: %s", lineID, buf );
		}
	}
	if ( fp != NULL ) {
		fclose(fp);
	}

	return 0;
}
