#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

int main()
{
	int c;
	FILE *fin;

	fin = fopen("infile.txt", "r");
	if ( fin == NULL) {
		printf("%s: %s\n", "infile.txt", strerror(errno));
		exit(-1);
	}

	do {
		c = fgetc( fin );

		if ( c != EOF ) {
			printf("%c", (char)c);
		}
	} while ( c != EOF );
	fclose( fin );

	return 0;
}
