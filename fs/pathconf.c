/*
 ** 获取系统目录最大长度
 ** <unistd.h>  
 ** char *getcwd( char *buffer, size_t size )
 ** long pathconf( char *path, int name )
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main( void )
{
	long cur_path_len;
	char *cur_work_dir;

	//cur_work_dir = NULL;

	/* 获取目录的最大长度 */
	if ( ( cur_path_len = pathconf( ".", _PC_PATH_MAX )) == -1 ) {
		perror( "Couldn't get current working path length !" );
		return 1;
	}
	printf( "Current Path Length Is : %ld\n", cur_path_len );
	
	/* 根据获取目录的最大长度，分配内存 */
	if ( (cur_work_dir = ( char* ) malloc( cur_path_len )) == NULL ) {
		perror( "Couldn't allocate memory for the pathname !" );
		return 1;
	}

	/* 得到当前工作目录 */
	if ( getcwd( cur_work_dir, cur_path_len ) == NULL ) {
		perror( "Couldn't get current directory!" );
		return 1;
	} 
	printf( "Current Directory Is : %s\n", cur_work_dir );

	return 0;
}
