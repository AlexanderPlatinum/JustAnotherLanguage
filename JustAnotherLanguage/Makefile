CC=g++
CFLAGS=-std=c++11 -g -Wall 

build: prepair Lexer.o Machine.o Parser.o Main.o
	$(CC) $(CFLAGS) ./obj/*.o -o compiler

Lexer.o:
	$(CC) $(CFLAGS) -c Lexer.cpp -o ./obj/Lexer.o

Machine.o:
	$(CC) $(CFLAGS) -c Machine.cpp -o ./obj/Machine.o 

Parser.o:
	$(CC) $(CFLAGS) -c Parser.cpp -o ./obj/Parser.o

Main.o:
	$(CC) $(CFLAGS) -c Main.cpp -o ./obj/Main.o

prepair:
	mkdir ./obj/

clean:
	rm -r ./obj/
	rm compiler