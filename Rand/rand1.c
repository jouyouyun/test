#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void)	
{

	int i;
	time_t t;

	srand((unsigned) time(&t));

	printf("Ten random numbers from 0 to 99\n");

	for (i=0; i<10; i++)
		printf("%d\n", rand() % ( 60 - 40 + 1) + 40);

	return 0;
}
