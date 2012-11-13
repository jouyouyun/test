/*
 ** rmdir
 ** int rmdir( const char *pathname )
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	char *pathname = "/home/wen/mkdir";

	if ( rmdir( pathname ) == -1 ) {
		perror( "Couldn't remove the diretory !");
		return 1;
	}

	return 0;
}
