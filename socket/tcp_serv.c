/* 套接字通信程序实例，通信域为 PF_INET */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <errno.h>

/*
 *	捕获子进程退出信号，在退出时给出提示
 */
void sig_handler( int signo )
{
	pid_t pid;
	int stat;

	pid = waitpid( -1, &stat, WNOHANG );
	while ( pid > 0 ) {
		printf( "child process terminated (PID: %ld)\n", (long)getpid() );
		pid = waitpid( -1, &stat, WNOHANG );
	}

	return ;
}

int main( int argc, char *argv[] )
{
	socklen_t clt_len;
	int listen_fd;
	int com_fd;
	int ret;
	int i;
	int len;
	int port;
	pid_t pid;
	static char recv_buf[1024];

	struct sockaddr_in clt_addr;
	struct sockaddr_in srv_addr;

	/* 服务器运行时要给出端口 */
	if ( argc != 2 ) {
		printf( "Usages: %s port\n", argv[0] );
		exit(-1);
	}

	/* 获得输入的端口 */
	port = atoi( argv[1] );

	/* 设置信号处理函数，也可以使用 sigaction 函数 */
	if ( signal( SIGCHLD, sig_handler ) < 0 ) {
		perror( "cannot set the signal" );
		exit(-1);
	}

	/* 创建套接字用于服务器的监听 */
	listen_fd = socket( PF_INET, SOCK_STREAM, 0 );
	if ( listen_fd == -1 ) {
		perror( "cannot create listening socket" );
		exit(-1);
	}

	memset( &srv_addr, 0, sizeof(srv_addr) );
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons( port );
	srv_addr.sin_addr.s_addr = htonl( INADDR_ANY );

	ret = bind( listen_fd, ( struct sockaddr*)&srv_addr, sizeof(srv_addr) );
	if ( ret == -1 ) {
		perror( "cannot bind the server socket" );
		close(listen_fd);
		exit(-1);
	}

	/* 监听制定端口，连接5个客户端 */
	ret = listen( listen_fd, 5 );
	if ( ret == -1 ) {
		perror( "cannot listen the port" );
		close( listen_fd );
		exit(-1);
	}

	/*
	 *	对每个连接来的客户端创建一个进程，单独与其通信
	 *	首先调用 read 函数读取客户端发来的信息
	 *	将其转换成大写后发送回客户端
	 *	当属入 ‘@’ 时退出
	 */
	while (1) {
		clt_len = sizeof(clt_addr);
		com_fd = accept( listen_fd, (struct sockaddr*)&clt_addr, &clt_len );
		if ( com_fd == -1 ) {
			if ( errno == EINTR ) {
				continue;
			} else {
				perror( "cannot accept client connect request" );
				close(listen_fd);
				exit(-1);
			}
		}

		pid = fork();
		if ( pid == -1 ) {
			perror( "cannot create the child process" );
			close(listen_fd);
			exit(-1);
		} else if ( pid == 0 ) {
			while ( (len = read( com_fd, recv_buf, 1024)) > 0 ) {
				printf( "Message from client(%d): %s\n", len, recv_buf );
				if ( recv_buf[0] == '@' ) {
					break;
				}

				for ( i = 0; i < len; i++ ) {
					recv_buf[i] = toupper( recv_buf[i] );
				}
				write( com_fd, recv_buf, len );
			}

			close(com_fd);
			exit(-1);
		} else {
			close( com_fd );
		}
	}

	return 0;
}
