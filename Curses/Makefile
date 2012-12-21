CC = gcc
#mingw32
#CC = i486-mingw32-gcc

PROG_NAME = win

OBJS := ${PROG_NAME}.o my_curses.o

CFLAG  = -Wall -g  -lcurses
LDFLAG = -Wall -g  -lcurses

all : ${PROG_NAME}

%.o : %.c
	${CC} ${CFLAG} -c $<

${PROG_NAME} : ${OBJS}
	${CC} ${LDFLAG} $^ -o $@

clean :
	rm -rf *.o ${PROG_NAME}

rebuild : clean all
