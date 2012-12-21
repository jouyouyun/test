/*
 * Curses Editor
 */

#include "my_curses.h"
#include <unistd.h>

int
main( int argc, char *argv[] )
{
	int ch;
	int i = 0;
	int flag = 0;		/* 退出标志 */
	int save_flag = 0;	/* 保存标志 */
	int x = StartX;
	int y = StartY;
	char buffer[MAX_BUF_SIZE];
  
	init_curses ();
	box (stdscr, ACS_VLINE, ACS_HLINE);
	attron (A_REVERSE);	/* 反色 */
	mvaddstr (0, COLS / 2 - 21 , "Curses Editor | F2 -- Save | Esc -- Exit");
	attroff (A_REVERSE);
	move (x, y);
	
	new_flag = 0;
	memset( buffer, 0, MAX_BUF_SIZE );
	while (1) {
		ch = getch ();
		switch (ch) {
			case KEY_UP:
				if (--y == 0) {
					y = 1;
				}
				break;
			case KEY_DOWN:
				if (++y == LINES - 1) {
					y -= 1;
				}
				break;
			case KEY_RIGHT:
				if (++x == COLS - 1) {
					x -= 1;
				}
				break;
			case KEY_LEFT:
				if (--x == 0) {
					x = 1;
				}
				break;
			case '\r':		/* Enter */
				if (++y == LINES - 1) {
					y -= 1;
				}
				x = 1;
				break;
			case '\t':		/* Tab */
				x += 7;
				if (x == COLS - 1) {
					x -= 1;
				}
				break;
			case 127:		/* BackSpace */
				if (--x == 0) {
					x = 1;
				} else {
					mvaddstr (y, --x, " ");
					buffer[i - 1] = '\0';
				}
				break;
			case 27:		/* ESC */
				flag = 1;
				break;
			case KEY_F(2):
				//fprintf( stdout, "F2: %d\n", KEY_F(2) );
				write_file( buffer );
				memset( buffer, 0, MAX_BUF_SIZE );
				i = 0;
				new_flag = 1;
				save_flag = 1;
				break;
			default:
				addch (ch);
				x++;
				if ( is_full( buffer ) ) {
					write_file( buffer );
					memset( buffer, 0, MAX_BUF_SIZE );
					i = 0;
					new_flag = 1;
				}
				buffer[i] = (char)ch;
				i++;
				break;
		}
		
		if (flag) {
			break;
		}
		
		move (y, x);
	} 

	endwin ();
	if ( save_flag == 0 ) {
		unlink( "/tmp/tmp" );
	}

	return 0;
}
