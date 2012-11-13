/*
 *	waitpid example
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid, wait_pid;
	int status;

	if ( ( pid = fork() ) == -1 ) {
		perror( "Cannot create process" );
		exit(1);
	} else if ( pid == 0 ) {
		/*
		 *	显示当前子进程，并让其处于等待中
		 */
		printf( "child pid: %ld\n", (long)getpid() );
		pause();

		_exit(0);
	} else {
		do {
			/* 使用 waitpid 等待子进程状态发生改变 */
			wait_pid = waitpid( pid, &status, WUNTRACED | WCONTINUED );
		
			if ( wait_pid == -1 ) {
				perror( "Cannot using waitpid function" );
				exit(1);
			}

			if ( WIFEXITED(status) ) {
				printf( "child process exites, status = %d\n", WEXITSTATUS(status) );
			}

			if ( WIFSIGNALED(status) ) {
				printf( "child process is killed by signal %d\n", WTERMSIG(status) );
			}

			if ( WIFSTOPPED(status) ) {
				printf( "child process is stopped by signal %d\n", WSTOPSIG(status) );
			}

			if ( WIFCONTINUED(status) ) {
				printf( "child process resume running ...\n" );
			}
		} while ( !WIFEXITED(status) && !WIFSIGNALED(status) );

		exit(0);
	}
}
