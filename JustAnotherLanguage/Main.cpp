#include <iostream>

#include "Lexer.h"
#include "Parser.h"

int main(int argc, char **argv)
{

	// Lexer
	Lexer lexer;

	lexer.Initialize("{ if ( 10 < 20 ) { a := 10 + 20 * ( 18 * 10 + 12 ); } b:= 30 + 37; }");
	lexer.Run();

	std::vector<Token> tokens = lexer.GetTokens();
	lexer.PrintTokens();

	// Parser
	Parser parser;

	parser.Initialize( tokens );
	parser.Run();

	std::vector<Operation> operations = parser.GetOperations();
	parser.PrintInfix();


	// End
	std::system("pause");

	return 0;
}
