#include <iostream>

#include "Lexer.h"

int main(int argc, char **argv)
{
	Lexer lexer;

	lexer.Initialize("def main ( argc, argv ) { for i in range(5) { } while ( a < b ) { a := 10; } return 0; }");
	lexer.Run();

	std::vector<Token> tokens = lexer.GetTokens();
	lexer.PrintTokens();

	std::system("pause");

	return 0;
}