/*
 * Peter
 */

#include "shmem.h"

int main( int argc, char *argv[] )
{
	char *shm_addr;
	key_t semkey, shmkey;
	struct sembuf getsem, setsem;
	int ret;
	int semid, shmid;
	int quit_flag = 0;

	semkey = ftok( FILENM, PROJID );
	if ( semkey == -1 ) {
		perror( "semkey ftok err" );
		exit(-1);
	}

	semid = semget( semkey, 0, 0 );
	if ( semid == -1 ) {
		perror( "semget err" );
		exit(-1);
	}

	getsem.sem_num = 0;
	getsem.sem_op = -1;
	getsem.sem_flg = SEM_UNDO;

	setsem.sem_num = 1;
	setsem.sem_op = 1;
	setsem.sem_flg = SEM_UNDO;

	shmkey = ftok( FILENM, PROJID + 0x0F00 );
	if ( shmkey == -1 ) {
		perror( "shmkey ftok err" );
		exit(-1);
	}

	shmid = shmget( shmkey, 4096, 0 );
	if ( shmid == -1 ) {
		perror( "shmget err" );
		exit(-1);
	}

	shm_addr = (char*)shmat( shmid, NULL, 0 );
	if ( shm_addr == (char*)-1 ) {
		perror( "shmat err" );
		exit(0);
	}

	while (1) {
		ret = semop( semid, &getsem, 1 );
		if ( ret == -1 ) {
			perror( "semop getsem err" );
		}
		printf( "Lucy: %s\n", shm_addr );

		printf( "Peter: " );
		fgets( shm_addr, MAX_BUF_LEN, stdin );
		if ( strncmp( "quit", shm_addr, 4 ) == 0 ) {
			quit_flag = 1;
		}

		shm_addr[strlen(shm_addr) - 1] = '\0';
		ret = semop( semid, &setsem, 1 );
		if ( ret == -1 ) {
			perror( "semop setsem err" );
		}

		if ( quit_flag ) {
			if ( shmdt( shm_addr ) == -1 ) {
				perror( "shm_addr err:" );
			}
			exit(0);
		}
	}

	return 0;
}
