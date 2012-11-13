/*
 ** 冒泡
 */

#include<stdio.h>

int main()
{
	int i, j, tmp;
	int a[7] = {45, 21, 23, 12, 13, 63, 2};

	for ( i = 0; i < 7; i++ ){
		for ( j = 7 - 1; j > i; j-- ){
			if ( a[j - 1] > a[j] ){
				tmp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = tmp;
			}
		}
	}

	for ( i = 0; i < 7; i++ ){
		printf("%d\t", a[i]);
	}
	printf("\n");

	return 0;
}