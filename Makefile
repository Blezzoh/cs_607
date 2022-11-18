lib: exp330.o log330.o 
	ar r libmath330.a exp/exp330.o exp/log330.o
	cp libmath330.a ./lib

exp330.o: moving
	gcc -c exp/exp330.c -l include/math330.h

log330.o: moving
	gcc -c log/log330.c -l include/math330.h

moving:
	mkdir include
	mkdir lib
	cp math330.h ./include