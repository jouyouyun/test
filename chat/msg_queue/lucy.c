/*
 * Lucy
 */

#include "msg_queue.h"

int mqid;

void terminate_handler( int signo )
{
	msgctl( mqid, IPC_RMID, NULL );
	exit(0);
}

int main( int argc, char *argv[] )
{
	key_t mqkey;
	MSGBUF msg;
	int quit_flag = 0;

	mqkey = ftok( FILENM, PROJID );
	if ( mqkey == -1 ) {
		fprintf( stderr, "ftok err: %s\n", strerror(errno) );
		exit(-1);
	}

	mqid = msgget( mqkey, IPC_CREAT | IPC_EXCL | 0666 );
	if ( mqid == -1 ) {
		fprintf( stderr, "msgget err: %s\n", strerror(errno) );
		exit(-1);
	}

	signal( SIGINT, terminate_handler );
	signal( SIGTERM, terminate_handler );

	while (1) {
		fprintf( stdout, "Lucy: " );
		fgets( msg.mtext, MAX_BUF_LEN, stdin );
		if ( strncmp( "quit", msg.mtext, 4 ) == 0 ) {
			quit_flag = 1;
		}

		msg.mtext[strlen(msg.mtext) - 1] = '\0';
		msg.mtype = SNDMSG;
		msgsnd( mqid, &msg, strlen(msg.mtext) + 1, 0 );

		if ( quit_flag ) {
			msgctl( mqid, IPC_RMID, NULL );
			exit(0);
		}

		msgrcv( mqid, &msg, MAX_BUF_LEN, RCVMSG, 0 );
		fprintf( stdout, "Peter: %s\n", msg.mtext );
	}

	return 0;
}
