/* shell 重定向 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ( int argc, char *argv[] )
{
	int f_des[2];
	int pid;

	if ( argc != 3 ) {
		printf( "Usage: %s command1 command2\n", argv[0] );
		exit(-1);
	}

	if ( pipe(f_des) == -1 ) {
		perror( "Cannot create the IPC pipe" );
		exit(-1);
	}

	if ( (pid = fork()) == - 1 ) {
		perror( "Cannot create the process" );
		exit(-1);
	} else if ( pid == 0 ) {
		/*
		 *	将管道的写入文件描述符重定向到标准输出
		 *	这样命令执行的结果将通过管道发送到父进程
		 */
		dup2( f_des[1], STDOUT_FILENO );

		close(f_des[0]);
		close(f_des[1]);

		if ( execlp( argv[1], argv[1], NULL ) == -1 ) {
			perror( "in child process, Cannot execute the command" );
			exit(-1);
		}
		return 1;
	} else {
		/*
		 *	将管道的读取文件描述符重定向到标准输入
		 *	这样从子进程发来的数据将作为命令的输入参数
		 */
		dup2( f_des[0], STDIN_FILENO );

		close(f_des[0]);
		close(f_des[1]);

		if ( execlp( argv[2], argv[2], NULL ) == -1 ) {
			perror( "in parent process, Cannot execute the command" );
			exit(-1);
		}
		return 1;
	}

	return 0;
}
