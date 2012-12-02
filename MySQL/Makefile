CC = gcc

PROG_NAME = test

OBJS := test.o 

INCS = /usr/include/mysql/mysql

LIBS = /usr/lib/mysql/

CFLAG  = -Wall -g -I${INCS} -L${LIBS} -lmysqlclient
LDFLAG = -Wall -g -I${INCS} -L${LIBS} -lmysqlclient

all : ${PROG_NAME}

%.o : %.c
	${CC} ${CFLAG} -c $<

${PROG_NAME} : ${OBJS}
	${CC} ${LDFLAG} $^ -o $@

clean :
	rm *.o ${PROG_NAME}

rebuild : clean all
