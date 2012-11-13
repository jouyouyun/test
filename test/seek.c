/*
 *	test fseek, lseek
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int ret;
	FILE *fp;
	char str1[] = "dsgfsjdkkkkkk";
	char str2[] = "45555666666666676";

	if ( (fp = fopen( "/tmp/tmp", "w")) == NULL ) {
		perror( "fopen err" );
		exit(-1);
	}
	fseek( fp, 50, SEEK_SET );
	printf( "offset: %ld\n", ftell(fp) );
	ret = fwrite( str1, sizeof(char), strlen(str1), fp );
	if ( ret == -1 ) {
		perror( "fwrite er" );
		fclose(fp);
		exit(-1);
	}
	fseek( fp, 0, SEEK_SET );
	printf( "offset: %ld\n", ftell(fp) );
	ret = fwrite( str2, sizeof(char), strlen(str2), fp );
	if ( ret == -1 ) {
		perror( "fwrite er" );
		fclose(fp);
		exit(-1);
	}
	fclose(fp);

	return 0;
}
