CC = gcc

SER = server
CLI = client

CFLAG  = -Wall -g
LDFLAG = -Wall -g

all: ${SER} ${CLI}

${CLI}.o : ${CLI}.c
	${CC} ${CFLAG} -c $<

${SER}.o : ${SER}.c
	${CC} ${CFLAG} -c $<

${CLI} : ${CLI}.o
	${CC} ${LDFLAG} $< -o $@

${SER} : ${SER}.o
	${CC} ${LDFLAG} $< -o $@

clean :
	rm -rf *.o ${CLI} ${SER}

rebuild : clean all
