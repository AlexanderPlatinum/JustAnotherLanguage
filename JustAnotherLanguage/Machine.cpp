#include "Machine.h"

Machine::Machine()
	: pc ( 0 )
{
	this->AddOperation(OperationType::NUMBER,
		[this](Operation &op) -> void
		{
			PushStack(op.value);
		}
	);

	this->AddOperation(OperationType::PLUS,
		[this](Operation &op) -> void
		{
			unsigned int a = this->PopStack();
			unsigned int b = this->PopStack();

			this->PushStack(a + b);
		}
	);

	this->AddOperation(OperationType::MINUS,
		[this](Operation &op) -> void
		{
			unsigned int a = this->PopStack();
			unsigned int b = this->PopStack();

			this->PushStack(a - b);
		}
	);

	this->AddOperation(OperationType::MUL,
		[this](Operation &op) -> void 
		{
			unsigned int a = this->PopStack();
			unsigned int b = this->PopStack();

			this->PushStack(a * b);
		}
	);

	this->AddOperation(OperationType::DIV,
		[this](Operation &op) -> void
		{
			unsigned int a = this->PopStack();
			unsigned int b = this->PopStack();

			this->PushStack(a / b);
		}
	);

	this->AddOperation(OperationType::PRINT,
		[this](Operation &op) -> void
		{
			unsigned int a = this->PopStack();
			std::cout << a << std::endl;
		}
	);

	this->AddOperation(OperationType::GOTO,
		[this](Operation &op) -> void
		{
			this->SetPC(this->PopStack());
		}
	);

	this->AddOperation(OperationType::GOTO_F,
		[this](Operation &op) -> void
		{
			unsigned int newPC = this->PopStack();
			unsigned int flag = this->PopStack();

			if (static_cast<bool>(flag) == false)
			{
				this->SetPC(newPC);
			}
		}
	);

	this->AddOperation(OperationType::LESS,
		[this](Operation &op) -> void
		{
			unsigned int b = this->PopStack();
			unsigned int a = this->PopStack();

			unsigned int result = static_cast<unsigned int>(a < b);

			this->PushStack(result);
		}
	);

	this->AddOperation(OperationType::BIGGEST,
		[this](Operation &op) -> void
		{
			unsigned int b = this->PopStack();
			unsigned int a = this->PopStack();

			unsigned int result = static_cast<unsigned int>(a > b);

			this->PushStack(result);
		}
	);

	this->AddOperation(OperationType::EQUALS,
		[this](Operation &op) -> void
		{
			unsigned int b = this->PopStack();
			unsigned int a = this->PopStack();

			unsigned int result = static_cast<unsigned int>(a == b);

			this->PushStack(result);
		}
	);
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
		if (pc == program.size())
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

void Machine::SetPC( Word _pc )
{
	pc = _pc;
}