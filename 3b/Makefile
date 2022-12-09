prog: main3B.o functions.o image.o
	g++ -g -Wall -o proj3B main3B.o functions.o image.o 

main3B.o: main3B.C functions.h image.h
	g++ -g -Wall -c -I. main3B.C

functions.o: functions.C functions.h image.h
	g++ -g -Wall -c -I. functions.C

image.o: image.C image.h
	g++ -g -Wall -c -I. image.C

clean:
	rm *.o proj3B -f