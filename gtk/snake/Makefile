CC = gcc
PROG_NAME = snake

LIBS = gtk+-2.0
CFLAGS = `pkg-config --cflags --libs ${LIBS}` -Wall -g

OBJS = snake.o

all : ${PROG_NAME}

${PROG_NAME} : ${OBJS}
	${CC} -o ${PROG_NAME}  $^ ${CFLAGS}

%.o : %.c
	${CC} -c $< ${CFLAGS}

clean :
	rm -f *.o ${PROG_NAME}

rebuild : clean all
