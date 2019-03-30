#include <iostream>

#include "Lexer.h"
#include "Parser.h"
#include "Machine.h"

int main(int argc, char **argv)
{

	// Lexer
	Lexer lexer;

	lexer.Initialize("{ while ( 10 < 20 ) { a := 10 + 20 * ( 18 * 10 + 12 ); if ( 2 > 3 ) { c := 10 * 7; } if ( 10 = 20 ) { b:= 30 + 37; } }");
	lexer.Run();

	std::vector<Token> tokens = lexer.GetTokens();
	lexer.PrintTokens();

	// Parser
	Parser parser;

	parser.Initialize( tokens );
	parser.Run();

	std::vector<Operation> operations = parser.GetOperations();
	parser.PrintInfix();
	parser.AssemblyListing( "main.asm" );

	// Machine

	Machine *machine = new Machine();

	machine->SetProgramm(operations);

	machine->AddOperation( OperationType::NUMBER,
		[machine] ( Operation &op ) -> void {
			machine->PushStack(op.value);
		}
	);

	machine->AddOperation(OperationType::PLUS,
		[machine](Operation &op) -> void {
			unsigned int a = machine->PopStack();
			unsigned int b = machine->PopStack();

			machine->PushStack( a + b );
		}
	);

	machine->AddOperation(OperationType::MINUS,
		[machine](Operation &op) -> void {
			unsigned int a = machine->PopStack();
			unsigned int b = machine->PopStack();

			machine->PushStack(a - b);
		}
	);

	machine->AddOperation(OperationType::MUL,
		[machine](Operation &op) -> void {
			unsigned int a = machine->PopStack();
			unsigned int b = machine->PopStack();

			machine->PushStack(a * b);
		}
	);

	machine->AddOperation(OperationType::DIV,
		[machine](Operation &op) -> void {
			unsigned int a = machine->PopStack();
			unsigned int b = machine->PopStack();

			machine->PushStack(a / b);
		}
	);

	try
	{
		machine->Run();
	}
	catch ( RuntimeError &e )
	{
		std::cout << e.what() << std::endl;
	}

	delete machine;

	// End
	std::system("pause");

	return 0;
}
