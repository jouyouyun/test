CC = gcc

PROG_NAME = copy

CFLAG = -Wall -lpthread -g
LDFLAG = -Wall -lpthread -g

OBJS := thrd_file.o

all : ${PROG_NAME}

${PROG_NAME} : ${OBJS}
	${CC} ${LDFLAG}  $^ -o $@

%o : %c
	${CC} ${CFLAG} -c $<

clean :
	rm -rf *.o ${PROG_NAME}

rebuild : clean all
