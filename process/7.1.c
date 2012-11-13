/*
 *	了解进程各个不同数据段的位置
 */

#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int bss_var;
int data_var0 = 1;

int main()
{
	/* 输出进程地址信息 */
	printf( "below are address of types of process's mem\n" );
	printf( "Text location:\n" );
	printf( "\tAddress of main(Code Segment):%p\n", main );

	/* 栈地址 */
	printf( "----------------------------------------\n" );
	int stack_var0 = 2;
	printf( "Stack location:\n" );
	printf( "\tInitial end of stack:%p\n", &stack_var0 );

	int stack_var1 = 3;
	printf( "\tNew end of stack:%p\n", &stack_var1 );

	/* 数据段 */
	printf( "----------------------------------------\n" );
	printf( "Data location:\n" );
	printf( "\tAddress of data_var(Data Segment):%p\n", &data_var0 );
	static int data_var1 = 4;
	printf( "\tnew end of data_var(Data Segment):%p\n", &data_var1 );

	printf( "----------------------------------------\n" );
	printf( "BSS location:\n" );
	printf( "\tAddress of bss_var:%p\n", &bss_var );

	/* 堆地址 */
	printf( "----------------------------------------\n" );
	char *b = sbrk( (ptrdiff_t)0 );
	printf( "Heap location:\n" );
	printf( "\tInitial end of heap:%p\n", b );

	brk( b + 4 );
	b = sbrk( (ptrdiff_t)0 );
	printf( "\tNew end of heap:%p\n", b );

	return 0;
}
