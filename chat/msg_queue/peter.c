/*
 * Peter
 */

#include "msg_queue.h"

int main( int argc, char *argv[] )
{
	key_t mqkey;
	MSGBUF msg;
	int mqid;
	int quit_flag = 0;

	mqkey = ftok( FILENM, PROJID );
	if ( mqkey == -1 ) {
		fprintf( stderr, "ftok err: %s\n", strerror(errno) );
		exit(-1);
	}

	mqid = msgget( mqkey, 0 );
	if ( mqid == -1 ) {
		fprintf( stderr, "msgget err: %s\n", strerror(errno) );
		exit(-1);
	}

	while (1) {
		msgrcv( mqid, &msg, MAX_BUF_LEN, SNDMSG, 0 );
		fprintf( stdout, "Lucy: %s\n", msg.mtext );

		fprintf( stdout, "Peter: " );
		fgets( msg.mtext, MAX_BUF_LEN, stdin );
		if ( strncmp( "quit", msg.mtext, 4 ) == 0 ) {
			quit_flag = 1;
		}

		msg.mtext[strlen(msg.mtext) - 1] = '\0';
		msg.mtype = RCVMSG;
		msgsnd( mqid, &msg, strlen(msg.mtext) + 1, 0 );

		if ( quit_flag ) {
			exit(0);
		}
	}

	return 0;
}
