/*
 ** 直接选择排序
 */

#include<stdio.h>

int direct_select(int *p, int n);

int main()
{
	int i;
	int a[7]={15, 3, 5, 9, 7, 13, 6};

	direct_select(a, 7);
	printf("选择排序后：");
	for ( i = 0; i < 7; i++ ){
		printf("%d  ", a[i]);
	}
	printf("\n");

	return 0;
}

/*
 ** i 不变，k 指向最小值，j++.tmp 存储最小值.在一圈结束后换值
 */

int direct_select(int *p, int n)
{
	int i, j, k, tmp;

	for ( i = 0; i < n; i++ ){
		k = i;
		for ( j = i + 1; j < n; j++ ){
			if ( *(p + k) > *(p + j)){
				k = j;
			}	
		}
		if ( k != i ){
			tmp = *(p + k);
			*(p + k) = *(p + i);
			*(p + i) = tmp;
		}
	}

	return 0;
}
