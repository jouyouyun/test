/*
 ** 求质数，Eratosthenes 筛选法。第一步列出所有数，然后从第一个质数开始，也就是2，依次剔出它的倍数，
 ** 照此循环，没有被剔出的就是质数。
 */
 
 #include<stdio.h>
 
 #define N 1000
 #define FALSE  -1
 
 void eratos( int *p , int n ); 

int main()
{
	int n;
	int i;
	int a[N];
	
	printf("Enter a number(1 - 1000): ");
	scanf("%d", &n);
	
	for ( i = 0; i < n - 1; i++ ) {
		a[i] = i + 2;
	}
	
	/* 筛选法求质数 */
	eratos( a , n );
	
	/* 输出所有质数 */
	for ( i = 0; i < n - 1; i++ ) {
		if ( a[i] > 0 ) {
			printf("%d  ", a[i]);
		}
	}
	printf("\n");
	
	return 0;
}

void eratos( int *p , int n )
{
	int i, j;
	
	for ( i = 0; i < n - 1; i++ ) {
		if( p[i] > 0 ){
			for ( j = i + 1; j < n - 1; j++ ){
				if ( p[j] % p[i] == 0 ){
					p[j] = FALSE;
				}
			}
		}
	}
}
			
	
