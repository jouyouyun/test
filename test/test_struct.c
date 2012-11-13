#include <stdio.h>
#include <stdlib.h>

typedef struct Test {
	int a;
	char *str;
}Test1;

typedef struct Temp {
	int  s;
	Test1 test;
}Tmp;

int main()
{
	Tmp tmp;

	tmp.s = 12;
	tmp.test.a = 34;
	tmp.test.str = "sfs";

	printf("s = %d\ta = %d\n", tmp.s, tmp.test.a);
	printf("str: %s\n", tmp.test.str);

	return 0;
}
