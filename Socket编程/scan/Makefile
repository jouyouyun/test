all = main.o bilscan.o scanmodule.o multiscan.o help.o
lib = -lpthread
scan : $(all)
	gcc -o scan $(all) $(lib)

main.o : main.c
	gcc -c main.c
bilscan.o : bilscan.c
	gcc -c bilscan.c
scanmodule.o : scanmodule.c
	gcc -c scanmodule.c
multiscan.o : multiscan.c
	gcc -c multiscan.c
help.o : help.c
	gcc -c help.c
