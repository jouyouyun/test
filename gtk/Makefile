CC = gcc
PROG_NAME = hello_box
#头文件
#INCS = 

#编译GTK程序时要用到的库
LIBS = gtk+-3.0
CFLAGS =  -Wall -g `pkg-config --cflags --libs ${LIBS}`
LDFLAGS =  -Wall -g `pkg-config --cflags --libs ${LIBS}`

#从xx.c 文件得到 xx.o 文件
OBJS := hello_box.o 

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
