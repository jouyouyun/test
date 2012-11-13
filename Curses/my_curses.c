/* My Curses funs */

#include "my_curses.h"

void init_curses()
{
	/* 开启 curses 模式 */
	initsrc();

	/* 
	 * 开启 cbreak 模式，除了DELETE\CTRL 等仍被视为特殊控制字元外
	 * 一切输入的字符将立刻被一一读取 
	 */
	cbreak();

	/*
	 * 用来决定当输入资料时
	 * 按下 RETURN 键是否被对应为 NEWLINE 字符
	 */
	nonl();

	/*
	 * echo() and noecho()
	 * 此函式用来控制从键盘输入字元时是否将字元显示在终端机上
	 */
	noecho();

	intrflush( stdsrc, false );

	/*
	 * 当开启 keypad 後, 可以使用键盘上的一些特殊字符
	 * 如上下左右>等方向键
	 */
	keypad( stdsrc, true );

	/* 将做清除萤幕的工作 */
	refresh();
}
