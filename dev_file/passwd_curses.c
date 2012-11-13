/*
 *	使用 curses 实现密码输入
 */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

void init()
{
	initscr();
	cbreak();
	nl();
	noecho();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	refresh();
}

int getpasswd( char *passwd, int size )
{
	int c;
	int n = 0;

	printf("Please Input password:");

	do {
		c = getch();

		if ( c != '\n' ) {
			echochar('*');	//printf("*");
			passwd[n++] = c;
		}
	} while ( c != '\n' && n < size - 1 );

	passwd[n] = '\0';

	return n;
}

int main()
{
	int n;
	char passwd[20];

	init();
	n = getpasswd( passwd, sizeof(passwd) );

	printf( "\nYour passwd is: %s\n", passwd );
	printf( "Please Enter any key continue ...\n" );

	refresh();
	getchar();
	endwin();

	return 0;
}
