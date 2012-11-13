#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

int main( int argc, char* argv[] )
{
	/* 定义类型为 stat 的结构体 file_stat，用于保存获得的文件信息 */
	struct stat file_stat;
	
	/* 
	 * 判断程序是否有一个参数执行，如果不是，给出提示 
	 * 程序运行结束
	 */
	if ( argc != 2 ) {
		printf( "Usage:%s filename\n", argv[0] );
		return 1;
	}
	
	/* 调用 stat 函数，如果出现错误，给出错误提示，程序退出 */
	if ( stat(argv[1], &file_stat ) == -1 ) {
		perror( "Cannot get the information of the file !\n" );
		return 1;
	}
	
	/* 使用 POSIX 中定义的宏判断是否是常规文件 */
	if ( S_ISREG( file_stat.st_mode ) ) {
		printf( "%s is Regular File, Juged by S_ISREG\n", argv[1] );
	}
	
	/* 通过 st_mode 与 S_IFREG 的位运算判断是否是常规文件 */
	if ( file_stat.st_mode & S_IFREG ) {
		printf("%s is regular file, juged by bits calculate S_IFREG\n", argv[1] );
	}
	
	/* 通过 S_ISDIR 宏判断是否是目录 */
	if ( S_ISDIR(file_stat.st_mode) ) {
		printf("%s is directory,juged by S_ISDIR.\n", argv[1] );
	}
	
	/* 通过 st_mode 与 S_IFDIR 的位运算判断是否是目录 */
	if ( file_stat.st_mode & S_IFDIR ) {
		printf("%s is directory,juged bi bits calculate.\n", argv[1] );
	}
	
	/* 输出 file_stat 中的其他文件信息 */
	printf("Owner ID: %d, Group ID: %d\n", file_stat.st_uid, file_stat.st_gid );
	printf("Perminssion: %o\n", file_stat.st_mode & 0x1ff );
	printf("Last Acess Time: %15s\n", ctime(&file_stat.st_atime) );
	printf("Last Modification Time: %15s\n", ctime(&file_stat.st_mtime) );
	printf("Last Status Change Time: %15s\n", ctime(&file_stat.st_ctime) );
	
	return 0;
}
