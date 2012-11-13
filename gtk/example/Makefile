CC = gcc
PROG_NAME = test
#头文件
#INCS = 

#编译GTK程序时要用到的库
PKG = `pkg-config --cflags --libs ${LIBS}`
LIBS = gtk+-3.0
CFLAGS =  -Wall -g ${PKG}
LDFLAGS =  -Wall -g ${PKG}

#从xx.c 文件得到 xx.o 文件
OBJS := draw.o 

all : ${PROG_NAME}

${PROG_NAME} : ${OBJS}
	${CC} ${LDFLAGS} $^ -o ${PROG_NAME}


#如果有头文件进行修改，则自动编译源文件
#${OBJS} : ${INCS}

%.o : %.c
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o ${PROG_NAME}

rebuild : clean all
