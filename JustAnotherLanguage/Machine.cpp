#include "Machine.h"

Machine::Machine()
	: pc ( 0 )
{
}

void Machine::SetProgramm( const Programm &program )
{
	this->program = program;
}

void Machine::AddOperation( const OperationType &op,
							std::function<void( Operation &op )> func )
{
	operations[op] = func;
}

void Machine::Run()
{
	while (true)
	{
		if (pc == program.size() - 1)
		{
			return;
		}

		Operation op = program[pc];
		if ( operations.find( op.type ) == operations.end() )
		{
			throw RuntimeError();
		}

		operations[op.type](op);
		pc++;
	}
}

void Machine::Reset()
{
	pc = 0;
	stack.clear();
}

void Machine::PushStack( Word word )
{
	stack.push_back( word );
}

Machine::Word Machine::PopStack()
{
	Word res = stack.back();
	stack.pop_back();

	return res;
}