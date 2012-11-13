/*
 *	利用 etext、edata、end 来分析内存
 *	这三个变量可获得进程的代码段、数据段和堆栈地址信息
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *	etext,edata,end 这三个变量在 Linux 库中已定义
 */
extern int etext, edata, end;

char *g_ptr = "Global String\n";
char g_buffer[20];

inline void disp_addr( char *p, int addr)
{
	printf( "Name :%s, Address:%0xd\n", p, addr ); 
}

/*
 *	disp_var 函数除了说明代码回位于代码段外
 *	还指出了使用 malloc 分配的空间位于堆中
 */

void disp_var( char *p )
{
	char *buffer;

	disp_addr( "buffer Address:", (int)(&buffer) );
	buffer = (char*)malloc(strlen(p) + 1);
	strcpy(buffer, p);
	printf( "buffer : %s\n", buffer );
	free(buffer);
}

int main()
{
	int i = 0;

	/* 以十六进制显示相关地址 */
	printf( "Addr etext : %0xd\n", (int)(&etext) );
	printf( "Addr edata : %0xd\n", (int)(&edata) );
	printf( "Addr end : %0xd\n", (int)(&end) );

	/* 显示各个函数和变量地址 */
	disp_addr( "function main() :", (int)(main) );
	disp_addr( "function disp_var:", (int)(disp_var) );
	disp_addr( "g_ptr address:", (int)(&g_ptr) );
	disp_addr( "g_buffer address:", (int)(&g_buffer) );
	disp_addr( "i address:", (int)(&i) );

	disp_var(g_ptr);
	return 0;
}
