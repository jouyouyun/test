/*
 ** mkdir
 ** int mkdir( const char *pathname, mode_t mode )
 */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	char *pathname = "/home/wen/mkdir";

	if ( mkdir( pathname, 0744 ) == -1 ) {
		perror( "Couldn't create the diretory !");
		return 1;
	}

	return 0;
}
