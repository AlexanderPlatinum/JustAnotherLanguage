build: Lexer.o Machine.o Parser.o Main.o
	g++ -std=c++11 ./obj/*.o -o compiler

Lexer.o:
	g++ -std=c++11 -c Lexer.cpp -o ./obj/Lexer.o

Machine.o:
	g++ -std=c++11 -c Machine.cpp -o ./obj/Machine.o 

Parser.o:
	g++ -std=c++11 -c Parser.cpp -o ./obj/Parser.o

Main.o:
	g++ -std=c++11 -c Main.cpp -o ./obj/Main.o