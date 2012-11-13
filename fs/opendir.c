#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *drt;
	
	if ( argc != 2 ) {
		printf("dir\n");
		return 1;
	}
	
	if ( (dir = opendir(argv[1])) == NULL ) {
		perror("Cannot open the diretion");
		return 1;
	}
	
	while ( (drt = readdir(dir)) != NULL ) {
		printf( "file_info : %d %d %s\n", (int)drt->d_ino, drt->d_reclen, drt->d_name );
	}
	closedir(dir);
	
	return 0;
}
