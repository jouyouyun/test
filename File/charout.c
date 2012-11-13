#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int i;
	FILE *fout;
	char str[] = {"This\r\nis a test\r\nfile.\r\n\0"};

	fout = fopen("infile.txt", "w");

	if ( fout == NULL ) {
		printf("%s: %s\n", "infile.txt", strerror(errno));
		exit(-1);
	}

	i = 0;
	while ( str[i] != '\0' ) {
		fputc( (int)str[i], fout);
		i++;
	}
	fclose(fout);

	return 0;
}
