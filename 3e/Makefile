SRC=main3E.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C
SRC3=main3C.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C
OBJ=$(SRC:.C=.o)
OBJ3=$(SRC3:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3E

prev: $(OBJ3)
	g++ $(OBJ3) -o proj3C


run: 
	./proj3E 3A_input.pnm writer.pnm

rprev: 
	./proj3C 3A_input.pnm writer.pnm

.C.o: $<
	g++ -I. -c $<

clean:
	rm *.o proj3E proj3C writer.pnm -f
