/*
 ** 大数相加，两个数中至少有一个超过 10 位
 */
 
 #include<stdio.h>
 #include<string.h>
 
 #define N 24
 
 void big_add( char *p, char *q, char *s );
 
 int main()
 {
 	char s1[N];
 	char s2[N];
 	char sum[N];
 	
 	printf("请输入两个数：");
 	scanf("%s%s", s1, s2 );
 	
 	if ( strlen(s1) > strlen(s2) ) {
 		big_add( s1, s2, sum );
 	} else {
 		big_add( s2, s1, sum );
 	}
 	printf("两数之和为：%s\n", sum);
 	
 	return 0;
 }
 
 /*
  ** big_add() 计算两数之和
  ** *p 表示长的数, *q 表示短的数, *s 表示两数之和
  */
 
 void big_add( char *p, char *q, char *s )
 {
 	int i, flag, tmp, d;
 	int len1 = strlen( p );
 	int len2 = strlen( q );
 	
 	flag = 0;  //表示是否进位
 	d = len1 - len2;
 	for ( i = len1 - 1; i >= 0; i-- ) {
 		/* 两数还未加完 */
 		if ( i - d >= 0 ) {
 			s[i] = p[i] + q[i - d] - '0' + flag;
 			tmp = s[i] - '0';
 		
 			if ( tmp > 9 ) {
 				s[i] = (tmp % 10) + '0';
 				flag = 1;
 			} else {
 				flag = 0;
 			}
 		} else {	/* 长的数剩余的部分 */
 			s[i] = p[i] + flag;
 			tmp = s[i] - '0';
 		
 			if ( tmp > 9 ) {
 				s[i] = (tmp % 10) + '0';
 				flag = 1;
 			} else {
 				flag = 0;
 			}
 		}
 	}
 	s[len1] = '\0';
 }
 	
