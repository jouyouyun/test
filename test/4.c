#include <stdio.h>

int func(int a, int *b)
{
	static int c = 1;
	int d = 3;

	*b = d+a+c;
	c = a+d;

	return *b;
}

int main()
{
	int a = 1, b = 2, i = 0;

	for ( ; i < 3;i++) {
		a= func(a, &b);
		printf("%d,", a);
	}

	return 0;
}
