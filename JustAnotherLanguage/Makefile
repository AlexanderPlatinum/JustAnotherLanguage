build: prepair Lexer.o Machine.o Parser.o Main.o
	g++ -std=c++11 -Wall ./obj/*.o -o compiler

Lexer.o:
	g++ -std=c++11 -Wall -c Lexer.cpp -o ./obj/Lexer.o

Machine.o:
	g++ -std=c++11 -Wall -c Machine.cpp -o ./obj/Machine.o 

Parser.o:
	g++ -std=c++11 -Wall -c Parser.cpp -o ./obj/Parser.o

Main.o:
	g++ -std=c++11 -Wall -c Main.cpp -o ./obj/Main.o

prepair:
	mkdir ./obj/

clean:
	rm -r ./obj/
	rm compiler