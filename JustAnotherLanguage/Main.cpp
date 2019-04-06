#include <iostream>
#include <fstream>

#include "Lexer.h"
#include "Parser.h"
#include "Machine.h"

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

	// Lexer
	Lexer lexer;

	lexer.Initialize( file );
	lexer.Run();

	std::vector<Token> tokens = lexer.GetTokens();
	//lexer.PrintTokens();

	// Parsers
	Parser parser;

	parser.Initialize( tokens );
	parser.Run();

	std::vector<Operation> operations = parser.GetOperations();
	//parser.PrintInfix();
	//parser.AssemblyListing( "main.asm" );

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
