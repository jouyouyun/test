/*
 *	使用 tcgetsttr 和 tcsetattr 函数来解决密码输入的回显问题
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#define ECHOFLAGS ( ECHO | ECHOE | ECHOK | ECHONL )

/*
 *	函数 set_disp_mode 用于控制是否开启输入回显功能
 *	如果 option 为 0, 则关闭回显，为 1 则打开回显
 */

int set_disp_mode ( int fd, int option )
{
	int err;
	struct termios term;

	if ( tcgetattr( fd, &term ) == -1 ) {
		perror( "Cannot get the attribution of the terminal" );
		exit(-1);
	}

	if ( option ) {
		term.c_lflag |= ECHOFLAGS;
	} else { 
		term.c_lflag &= ~ECHOFLAGS;
	}

	err = tcsetattr ( fd, TCSAFLUSH, &term );
	if ( err == -1 && err == EINTR ) {
		perror( "Cannot set the attribution of the terminal" );
		exit ( -1 );
	}

	return 0;
}

/*
 *	函数 getpasswd 用于获得用户输入的密码，
 *	并将其保存到指定的字符数组中
 */

int getpasswd ( char *passwd, int size ) 
{
	int c;
	int n = 0;

	printf( "Please Input Password:" );
	do {
		c = getchar();

		if ( c != '\n' || c != '\r' ) {
			passwd[n++] = c;
		}
	} while ( c != '\n' && c != '\r' && n < ( size - 1 ) );

	passwd[n] = '\0';

	return 0;
}

int main()
{
	char passwd[20];

	/* 首先关闭回显，这样输入密码就不会显示输入的字符信息 */
	set_disp_mode( STDIN_FILENO, 0 );
	
	/* 调用 getpasswd 函数获得用户输入的密码 */
	getpasswd( passwd, sizeof(passwd) );

	printf( "\nYour passwd is:%s\n", passwd );
	printf( "Press any key continue ...\n" );

	set_disp_mode( STDIN_FILENO, 1 );
	getchar();

	return 0;
}
