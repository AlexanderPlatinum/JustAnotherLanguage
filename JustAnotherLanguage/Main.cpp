#include <iostream>

#include "Lexer.h"
#include "Parser.h"
#include "Machine.h"

int main(int argc, char **argv)
{

	// Lexer
	Lexer lexer;

	lexer.Initialize("{ if( 10 > 4 ) { a = (30 + 37) * 10; b = 15 * 18; } print( a ); print( b ); }");
	lexer.Run();

	std::vector<Token> tokens = lexer.GetTokens();
	lexer.PrintTokens();

	// Parsers
	Parser parser;

	parser.Initialize( tokens );
	parser.Run();

	std::vector<Operation> operations = parser.GetOperations();
	parser.PrintInfix();
	parser.AssemblyListing( "main.asm" );

	// Machine

	std::cout << "Start working machine >" << std::endl << std::endl;

	Machine *machine = new Machine();

	machine->SetProgramm(operations);

	try
	{
		machine->Run();
	}
	catch ( RuntimeError &e )
	{
		std::cout << e.what() << std::endl;
	}

	delete machine;

	#ifdef _WIN32
	std::system("pause");
	#endif

	return 0;
}
