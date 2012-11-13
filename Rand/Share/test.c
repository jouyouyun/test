/*
 * test randapi 
 * 
 */
 
 #include "randapi.h"
 #include<stdio.h>
 
 #define ITERATTIONS  1000000L
 
 int main()
 {
	 long  i;
	 long  isum;
	 float fsum;
	 
	 /* Initializes the random number API */
	 initrand();
	 
	 /* Find the average of getrand(10) return (0..9) */
	 isum = 0l;
	 for ( i = 0; i < ITERATTIONS; i++ ){
		 isum += getrand(10);
	 }
	 printf("getrand() Average %d\n", (int) (isum / ITERATTIONS) );
	 
	 /* Find the average of getsrand() returns */
	 fsum = 0.0;
	 for ( i = 0; i < ITERATTIONS; i++ ) {
		 fsum += getsrand();
	 }
	 printf("getsrand() Average %f\n", (fsum / (float) ITERATTIONS ) );
	 
	 return ;
}
