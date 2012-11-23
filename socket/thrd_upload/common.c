#include "my_sock.h"

char *get_name( char *path )
{
	char *name;
	char *tmp;
	char delim[] = "/";

	if ( path == NULL ) {
		printf( "get_name arguments err\n" );
		return NULL;
	}

	tmp = strtok( path, delim );
	name = tmp;

	while ( (tmp = strtok( NULL, delim )) != NULL ) {
		name = tmp;
	}

	return name;
}

int msg_recv( ARGS *args )
{
	int ret;
	
	if ( args == NULL ) {
		fprintf( stderr, "msg_recv arguments err!\n" );
		return -1;
	}
	
	memset( args->buffer, 0, MAX_BUF_SIZE );
	memset( args->file_dir, 0, MAX_DIR_LEN );
	ret = recvfrom( args->sockfd, args, sizeof(ARGS), 0, (struct sockaddr*)&args->addr, 
		&args->addr_len );
	if ( ret == -1 ) {
		fprintf( stderr, "msg_recv recvfrom err!\n" );
		return -1;
	}
	
	return 0;
}

int msg_send( ARGS *args )
{
	int ret;
	
	if ( args == NULL ) {
		fprintf( stderr, "msg_send arguments err!\n" );
		return -1;
	}
	
	ret = sendto( args->sockfd, args, sizeof(ARGS), 0, (struct sockaddr*)&args->addr, 
		args->addr_len );
	if (ret == -1 ) {
		fprintf( stderr, "msg_send sendto err: %s\n", strerror(errno) );
		return -1;
	}
	
	return 0;
}

int read_file( char *fname )
{
	int i, j;
	int ret;
	off_t size, len;
	struct stat buf;
	ARGS args[THRD_NUM];
	pthread_t thrds[THRD_NUM];
	//pthread_attr_t attr_detach;

	if ( fname == NULL ) {
		fprintf( stderr, "read_file arguments err!\n" );
		return -1;
	}

	if ( stat( fname, &buf ) == -1 ) {
		fprintf( stderr, "stat err: %s\n", strerror(errno) );
		return -1;
	}

	size = (off_t) buf.st_size;
	len = (off_t) ( buf.st_size / THRD_NUM );

	printf( "size: %ld\tlen: %ld\n", (long)size, (long)len );
	/* 设置属性： 独立线程 */
	//pthread_attr_init( &attr_detach );
	//pthread_attr_setdetachstate( &attr_detach, PTHREAD_CREATE_DETACHED);

	for ( i = 0; i < THRD_NUM; i++ ) {
		args[i].start = i * len;
		if ( i == THRD_NUM - 1 ) {
			args[i].len = size - args[i].start;
		} else {
			args[i].len = len;
		}
		memset( args[i].buffer, 0, MAX_BUF_SIZE );
		memset( args[i].path, 0, PATH_LEN );
		strcpy( args[i].path, fname );

		printf( "start: %ld\tend: %ld\n", (long)args[i].start, (long)args[i].len );
		ret = pthread_create( &thrds[i], 0, thrd_read, &args[i] );
		if ( ret != 0 ) {
			fprintf( stderr, "create thrd %d err: %s\n", i, strerror(errno) );
			for ( j = 0; j < i; j++ ) {
				pthread_cancel( thrds[i] );
			}
			return -1;
		}
	}

	for ( i = 0; i < THRD_NUM; i++ ) {
		pthread_join( thrds[i], NULL );
	}

	return 0;
}

void *thrd_read( void *arg )
{
	int len;
	FILE *fp;
	ARGS *args = ( ARGS* )arg;

	if ( args == NULL ) {
		fprintf( stderr, "thrd_read arguments err\n" );
		pthread_exit(NULL);
	}

	fp = fopen( args->path, "r" );
	if ( fp == NULL ) {
		fprintf( stderr, "open file err: %s\n", strerror(errno) );
		pthread_exit( NULL );
	}

	fseek( fp, args->start, SEEK_SET );
	while ( (!feof(fp)) && ( args->len > 0) ) {
		if ( args->start == 0 ) {
			args->first_flag = 1;
		} else {
			args->first_flag = 0;
		}

		if ( args->len > MAX_BUF_SIZE ) {
			len = fread( args->buffer, sizeof(char), MAX_BUF_SIZE, fp );
		} else {
			len = fread( args->buffer, sizeof(char), args->len, fp );
		}
		if ( len == -1 ) {
			fprintf( stderr, "fread err: %s\n", strerror(errno) );
			break;
		} else if ( len == 0 ) {
			fprintf( stderr, "file has closed\n" );
			break;
		}

		args->read_len = len;
		if ( msg_send( args ) == -1 ) {
			break;
		}

		args->start += len;
		args->len -= len;
	}

	fclose(fp);
	pthread_exit( NULL );
}

int write_file( ARGS *args )
{
	int len;
	FILE *fp;

	if ( args == NULL ) {
		fprintf( stderr, "write_file arguments err\n" );
		return -1;
	}

	if ( args->first_flag ) {
		fp = fopen( TMP, "w" );
	} else {
		fp = fopen( TMP, "a" );
	}
	if ( fp == NULL ) {
		fprintf( stderr, "write_file open err: %s\n", strerror(errno) );
		return -1;
	}

	//printf( "write_file: %ld\n", (long)args->start );
	fseek( fp, args->start, SEEK_SET );
	len = fwrite( args->buffer, sizeof(char), args->read_len, fp );
	if ( len == -1 ) {
		fprintf( stderr, "write err: %s\n", strerror(errno) );
		fclose(fp);
		return -1;
	}

	fclose(fp);
	return 0;
}
