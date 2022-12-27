SRC=main3D.C image.C sink.C source.C PNMreaderCPP.C PNMwriterCPP.C filter.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3D

.C.o: $<
	g++ -I. -c $<
run: 
	./proj3D 3A_input.pnm writer.pnm
clean:
	rm *.o proj3D -f


# main3E.o: main3E.C pnmwriter.o sink.o filter.o image.o source.o
# 	g++ -g -Wall -c -I. main3C.C

# run: 
# 	./test 3A_input.pnm test.pnm

# test: main.o filter.o pnmreader.o source.o image.o sink.o pnmwriter.o
# 	g++ -g -Wall -o test main.o PNMwriter.o sink.o PNMreader.o filter.o source.o image.o 

# main.o: pnmreader.o filter.o  source.o  image.o
# 	g++ -g -Wall -c -I. main.C


# pnmwriter.o:
# 	g++ -g -Wall -c -I. PNMwriter.C


# sink.o:
# 	g++ -g -Wall -c -I. sink.C

# filter.o:  pnmreader.o image.o filter.h image.h
# 	g++ -g -Wall -c -I. filter.C

# source.o: image.o
# 	g++ -g -Wall -c -I. source.C

	
# pnmreader.o: image.o source.o
# 	g++ -g -Wall -c -I. PNMreader.C

# image.o: image.C image.h
# 	g++ -g -Wall -c -I. image.C
	
# clean:
# 	rm *.o proj3E test.pnm test -f