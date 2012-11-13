/*
 ** pwd 获取当前路径
 ** <unistd.h>  
 ** char *getcwd( char *buffer, size_t size )
 ** <limits.h>
 ** PATH_MAX 可选常量，可能未定义，定义如下
 ** #define PATH_MAX 255
 */

#include <limits.h>
#include <stdio.h>
#include <unistd.h>

int main( void )
{
	char cur_dir[PATH_MAX];

	printf( "Current Max Path Length Is : %d\n", PATH_MAX );
	
	if ( getcwd( cur_dir, PATH_MAX ) == NULL ) {
		perror( "Couldn't get current directory!" );
		return 1;
	} 

	printf( "Current Directory Is : %s\n", cur_dir );

	return 0;
}
