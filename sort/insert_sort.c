/*
 ** 直接插入排序
 */

#include<stdio.h>

int direct_sort(int *p, int n);

int main()
{
	int i;
	int a[8] = {9, 5, 6, 4, 3, 11, 8, 10};

	direct_sort(a, 8);
	for( i = 0; i < 8; i++ ){
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}

/*
 ** 假定 i 前面的序列是有序的，j = i - 1, tmp = a[i] ,与 j 比较，大于跳过
 ** 小于则 j 后移。
 */

int direct_sort(int *p, int n)
{
	int i, j, tmp;

	for ( i = 1; i < n; i++ ){
		tmp = *(p + i);
		for ( j = i - 1; j >= 0; j-- ){
			if ( tmp < *(p + j) ){
				*(p + j + 1) = *(p + j);
			} else {
				break;
			}
		}
		*(p + j + 1) = tmp; 
	}

	return 0;
}
