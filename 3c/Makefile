SRC=main3E.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3E

.C.o: $<
	g++ -I. -c $<

pnmreader.o:
	g++ -g -Wall -c -I. PNMreader.C
image.o: image.C image.h
	g++ -g -Wall -c -I. image.C
	
clean:
	rm *.o proj3E