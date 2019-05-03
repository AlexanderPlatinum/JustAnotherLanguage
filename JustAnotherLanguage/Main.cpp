#include <iostream>
#include <fstream>

#include "Lexer.h"
#include "Parser.h"
#include "Machine.h"

#include "HashSet.h"

std::string getFileContent( const std::string &fileName )
{
	std::ifstream file( fileName );
	std::string temp = "";

	if ( ! file.is_open() )
	{
		std::cout << "File with name not open " << fileName << std::endl;
	}

	while( !file.eof() )
	{
		std::string temp2;
		std::getline( file, temp2 );

		temp += temp2;
	}

	return temp;
}

int main(int argc, char **argv)
{
	std::string file = getFileContent( argv[1] );

	Lexer lexer;
	lexer.Initialize( file );
	lexer.Run();

	std::vector<Token> tokens = lexer.GetTokens();

	Parser parser;
	parser.Initialize( tokens );
	parser.Run();

	std::vector<Operation> operations = parser.GetOperations();

	Machine machine;
	machine.SetProgramm(operations);

	try
	{
		machine.Run();
	}
	catch ( RuntimeError &e )
	{
		std::cout << e.what() << std::endl;
	}

	#ifdef PRINT_DEBUG
	lexer.PrintTokens();
	parser.PrintInfix();
	parser.AssemblyListing( "main.asm" );
	#endif

	#ifdef _WIN32
	std::system("pause");
	#endif

	return 0;
}
