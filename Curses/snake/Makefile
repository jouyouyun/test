CC = gcc

PROG_NAME = main

OBJS := ${PROG_NAME}.o my_snake.o my_draw.o

CFLAG  = -Wall -g  -lcurses -lpthread
LDFLAG = -Wall -g  -lcurses -lpthread

all : ${PROG_NAME}

%.o : %.c
	${CC} ${CFLAG} -c $<

${PROG_NAME} : ${OBJS}
	${CC} ${LDFLAG} $^ -o $@

clean :
	rm -rf *.o ${PROG_NAME}

rebuild : clean all
