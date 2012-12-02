/*
 * Lucy
 */

#include "shmem.h"

#if defined(_GUN_LIBRARY_) && !defined(_SEM_SEMUN_UNDEFINED)
/* union semun is defined ny including <sys/sem.h> */

#else
/* according to X/OPEN we have to define it ourselves */
union semun {
	int val;				/* value for SETVAL */
	struct semid_ds *buf;	/* buffer for IPC_STAT, IPC_SET */
	unsigned short *array;	/* array for GETALL, SETALL */
	/* Linux specific part */
	struct seminfo *_buf;	/* buffer for IPC_INFO */
};
#endif

int semid;
int shmid;

void terminate_handler( int signo )
{
	semctl( semid, 0, IPC_RMID );
	shmctl( shmid, IPC_RMID, NULL );
	exit(0);
}

int main( int argc, char *argv[] )
{
	char *shm_addr;
	key_t semkey;
	struct sembuf getsem, setsem;
	union semun seminit;
	key_t shmkey;
	int ret;
	int quit_flag = 0;

	semkey = ftok( FILENM, PROJID );
	if ( semkey == -1 ) {
		perror( "semkey ftok err" );
		exit(-1);
	}

	semid = semget( semkey, 2, IPC_CREAT | IPC_EXCL | 0666 );
	if ( semid == -1 ) {
		perror( "semget err" );
		exit(-1);
	}

	seminit.val = 0;
	semctl( semid, 0, SETVAL, seminit );
	semctl( semid, 1, SETVAL, seminit );

	getsem.sem_num = 1;
	getsem.sem_op = -1;
	getsem.sem_flg = SEM_UNDO;

	setsem.sem_num = 0;
	setsem.sem_op = 1;
	setsem.sem_flg = SEM_UNDO;

	signal( SIGINT, terminate_handler );
	signal( SIGTERM, terminate_handler );

	shmkey = ftok( FILENM, PROJID + 0x0F00 );
	if ( shmkey == -1 ) {
		perror( "shmkey ftok err" );
		exit(-1);
	}

	shmid = shmget( shmkey, 4096, IPC_CREAT | IPC_EXCL | 0666 );
	if ( shmid == -1 ) {
		perror( "shmget err" );
		exit(-1);
	}

	shm_addr = (char*)shmat( shmid, NULL, 0 );
	if ( shm_addr == (char*)-1 ) {
		perror( "shmat err" );
		semctl( semid, 0, IPC_RMID );
		shmctl( shmid, IPC_RMID, NULL );
		exit(0);
	}

	while (1) {
		printf( "Lucy: " );
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
			semctl( semid, 0, IPC_RMID );
			shmctl( shmid, IPC_RMID, NULL );
			exit(0);
		}

		ret = semop( semid, &getsem, 1 );
		if ( ret == -1 ) {
			perror( "semop getsem err" );
		}
		printf( "Peter: %s\n", shm_addr );
	}

	return 0;
}
