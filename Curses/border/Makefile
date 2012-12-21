CC = gcc

PROG_NAME = main

OBJS := ${PROG_NAME}.o my_curses.o game_move.o

CFLAG  = -Wall -g  -lcurses -lpthread -lm
LDFLAG = -Wall -g  -lcurses -lpthread -lm

all : ${PROG_NAME}

%.o : %.c
	${CC} ${CFLAG} -c $<

${PROG_NAME} : ${OBJS}
	${CC} ${LDFLAG} $^ -o $@

clean :
	rm -rf *.o ${PROG_NAME}

rebuild : clean all
