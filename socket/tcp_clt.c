/* 套接字通信程序实例，通信域为 PF_INET */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <netdb.h>

int main( int argc, char *argv[] )
{
	int ret;
	int len;
	int port;
	int connect_fd;
	char snd_buf[1024];

	static struct sockaddr_in srv_addr;

	/* 客户端运行需要给出具体的连接地址和端口 */
	if ( argc != 3 ) {
		printf( "Usages: %s IP port\n", argv[0] );
		exit(-1);
	}

	port = atoi(argv[2]);

	connect_fd = socket(PF_INET, SOCK_STREAM, 0 );
	if ( connect_fd == - 1 ) {
		perror( "cannot create communication socket" );
		exit(-1);
	}

	memset( &srv_addr, 0, sizeof(srv_addr) );
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port);
	srv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	/* 连接指定的服务器 */
	ret = connect( connect_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr) );
	if ( ret == -1 ) {
		perror( "cannot connect to the server" );
		close(connect_fd);
		exit(-1);
	}

	memset( snd_buf, 0, 1024 );
	/* 
	 *	用户输入信息后，程序会发送给服务器 
	 *	然后调用 read 函数读取服务器中的发来的信息
	 *	当输入 ‘@’ 时，程序退出
	 */
	while (1) {
		write( STDOUT_FILENO, "input message:", 14 );

		len = read( STDIN_FILENO, snd_buf, 1024 );
		if ( len > 0 ) {
			write( connect_fd, snd_buf, len );
		}

		len = read( connect_fd, snd_buf, len );
		if ( len > 0 ) {
			printf( "Message from server: %s\n", snd_buf );
		}

		if ( snd_buf[0] == '@' ) {
			break;
		}
	}

	close(connect_fd);
	return 0;
}
