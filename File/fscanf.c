/*
 * fscanf test
 */ 

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define BUF 1024

typedef struct player {
	int  number;
	char player_name[BUF];
	char title_name[BUF];
} PLAYER;

int main()
{
	int ret;
	int line;
	FILE *fp;
	PLAYER players[16];

	fp = fopen( "fscanf", "r" );
	if ( fp == NULL ) {
		fprintf( stderr, "open file err: %s\n", strerror(errno) );
		exit(-1);
	}

	line = 0;
	while ( !feof(fp) ) {
		memset( &players[line], 0, sizeof(PLAYER) );
		ret = fscanf( fp, "%d,%s,%s\n", &players[line].number, 
				players[line].player_name, players[line].title_name );
		fprintf( stdout, "%d\n", ret );
		if ( ret < 3 ) {
			fprintf( stderr, "fscanf err\n" );
			break;
		}

		fprintf( stdout, "%d,%s,%s", players[line].number, 
				players[line].player_name, players[line].title_name );
		line++;
	}
	fclose(fp);

	return 0;
}
