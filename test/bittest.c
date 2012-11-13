#include <stdio.h>

int main()
{
	int s;
	int num = 0x0001efab;

	s = (num >> 16) + (num & 0xffff);
	printf( "0x%x s = 0x%x\n", num, s );

	return 0;
}
