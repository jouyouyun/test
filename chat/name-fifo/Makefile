CC = gcc
#mingw32
#CC = i486-mingw32-gcc

LUCY  = Lucy
PETER = Peter

CFLAG  = -Wall -g
LDFLAG = -Wall -g

all: ${LUCY} ${PETER}

lucy.o : lucy.c
	${CC} ${CFLAG} -c $<

peter.0 : peter.c
	${CC} ${CFLAG} -c $<

${LUCY} : lucy.o
	${CC} ${LDFLAG} $< -o $@

${PETER} : peter.o
	${CC} ${LDFLAG} $< -o $@

clean :
	rm -rf *.o ${LUCY} ${PETER}

rebuild : clean all
