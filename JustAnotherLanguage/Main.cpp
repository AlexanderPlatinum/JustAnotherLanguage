#include <iostream>

#include "Lexer.h"

int main(int argc, char **argv)
{
	Lexer lexer;

	lexer.Initialize("def main () { while ( a < b ) { a := 10 } }");
	lexer.Run();

	std::vector<Token> tokens = lexer.GetTokens();
	lexer.PrintTokens();

	std::system("pause");

	return 0;
}