bin: lib
	mkdir -p bin
	gcc -c cli/cli.c -I include/
	mv cli.o lib
	gcc -o bin/cli lib/cli.o lib/libmath330.a -lm

lib: expo trig 
	ar r libmath330.a lib/exp330.o lib/log330.o lib/cos330.o lib/sin330.o lib/tan330.o
	mv libmath330.a lib/

trig: moving
	gcc -c trig/cos330.c -I include/
	gcc -c trig/sin330.c -I include/
	gcc -c trig/tan330.c -I include/
	mv cos330.o sin330.o tan330.o lib/

expo: moving
	gcc -c exp/exp330.c -I include/
	gcc -c exp/log330.c -I include/
	mv exp330.o lib/
	mv log330.o lib/

moving: clean
	mkdir include
	mkdir lib
	cp math330.h ./include

clean:
	if [ -d include/ ]; then rm -r include; fi;
	if [ -d lib/ ]; then rm -r lib; fi;
	if [ -d bin/ ]; then rm -r bin; fi;