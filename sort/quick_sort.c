/*
 ** 快速排序
 */

#include<stdio.h>

int quick(int *a, int left, int right )
{
	int key = a[left];

	while ( left < right ){
		while (left < right && a[right] >= key) {
			right--;
		}	
		a[left] = a[right];   //换值

		while (left < right && a[left] <= key) {
			left++;
		}	
		a[right] = a[left];   //换值
	}
	a[left] = key;

	return left;
}

void quick_sort( int *a, int left, int right )
{
	int base;

	if ( left < right ){
		base = quick(a, left, right);
		//以 key 为中心，分成两个数组进行递归排序
		quick_sort(a, left, base - 1);
		quick_sort(a, base + 1, right);
	}

}

int main()
{
	int i;
	int a[8]={1, 5, 6, 2,77, 54, 32, 44};

	quick_sort(a, 0, 7);

	for ( i = 0; i < 8; i++ ){
		printf("%d  ", a[i]);
	}
	printf("\n");

	return 0;
}
