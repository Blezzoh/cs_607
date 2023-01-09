SRC=main3G.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C logging.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3G

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o proj3G 3A_input.pnm writer.pnm -f

run: 
	./proj3G input.pnm writer.pnm



runt: 
	./test input.pnm test.pnm

main.o: pnmreader PNMwriter filter.o source.o image.o sink.o
	g++ -g -Wall -c -I. main.C

pnmreader: 
	g++ -g -Wall -c -I. PNMreader.C

PNMwriter: 
	g++ -g -Wall -c -I. PNMwriter.C

filter.o:
	g++ -g -Wall -c -I. filter.C

sink.o:
	g++ -g -Wall -c -I. sink.C

source.o:
	g++ -g -Wall -c -I. source.C

logger.o:
	g++ -g -Wall -c -I. logging.C
	

test: main.o filter.o pnmreader source.o image.o sink.o PNMwriter  logger.o
	g++ -g -Wall -o test main.o PNMwriter.o sink.o PNMreader.o logging.o filter.o source.o image.o 

