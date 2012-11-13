#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
	int fd1, fd2;
	struct stat file_stat;
	
	/*
	 * 创建名为 test1 的文件，权限为 777
	 */
	fd1 = open("test", O_CREAT | O_RDWR, 0777);
	
	/*
	 * 判断文件是否创建成功，如果失败，给出提示
	 */
	if ( fd1 < 0 ) {
		perror("Cannot creat the test file\n");
		return 1;
	}
	/* 关闭文件 */
	close(fd1);
	
	/* 调用 stat 函数获得 test 文件的权限 */
	if ( stat("test", &file_stat) == -1 ) {
		perror("Cannot get the information of the file!\n");
		return 1;
	}
	/* 输出权限值 */
	printf("Premission is: %o\n", file_stat.st_mode & 0x1ff );
	
	/*
	 * 调用 umask 函数修改进程创建文件的 umask 值
	 * 除了使用下面的形式外，还可以使用 umask(077) 这样的形式
	 */
	umask( S_IWGRP | S_IRGRP | S_IXGRP | S_IWOTH | S_IROTH | S_IXOTH );
	
	/* 创建名为 test1 的文件，权限为 777 */
	fd2 = open("test1", O_CREAT | O_RDWR, 0777);
	
	if (fd2 < 0) {
		perror("Cannot creat the test1 file!\n");
		return 1;
	}
	close(fd2);
	
	/* 调用 stat 函数获取 test1 的权限值 */
	if ( stat("test1", &file_stat) == -1 ) {
		perror("Cannot get the information of the file!\n");
		return 1;
	}
	printf("After Modify umask value, Premission is: %o\n", file_stat.st_mode & 0x1ff );
	
	return 0;
}