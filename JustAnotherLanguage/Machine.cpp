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
			Word a = this->PopStack();
			Word b = this->PopStack();

			this->PushStack(a + b);
		}
	);

	this->AddOperation(OperationType::MINUS,
		[this](Operation &op) -> void
		{
			Word a = this->PopStack();
			Word b = this->PopStack();

			this->PushStack(a - b);
		}
	);

	this->AddOperation(OperationType::MUL,
		[this](Operation &op) -> void 
		{
			Word a = this->PopStack();
			Word b = this->PopStack();

			this->PushStack(a * b);
		}
	);

	this->AddOperation(OperationType::DIV,
		[this](Operation &op) -> void
		{
			Word a = this->PopStack();
			Word b = this->PopStack();

			this->PushStack(a / b);
		}
	);

	this->AddOperation(OperationType::PRINT,
		[this](Operation &op) -> void
		{
			Word value = this->PopStack();
			std::cout << value << std::endl;
		}
	);

	this->AddOperation(OperationType::GOTO,
		[this](Operation &op) -> void
		{
			Word address = this->PopStack();
			this->SetPC( address );
		}
	);

	this->AddOperation(OperationType::GOTO_F,
		[this](Operation &op) -> void
		{
			Word newPC = this->PopStack();
			Word flag = this->PopStack();

			if (static_cast<bool>(flag) == false)
			{
				this->SetPC(newPC);
			}
		}
	);

	this->AddOperation(OperationType::LESS,
		[this](Operation &op) -> void
		{
			Word b = this->PopStack();
			Word a = this->PopStack();

			Word result = static_cast<Word>(a < b);

			this->PushStack(result);
		}
	);

	this->AddOperation(OperationType::BIGGEST,
		[this](Operation &op) -> void
		{
			Word b = this->PopStack();
			Word a = this->PopStack();

			Word result = static_cast<Word>(a > b);

			this->PushStack(result);
		}
	);

	/*this->AddOperation(OperationType::EQUALS,
		[this](Operation &op) -> void
		{
			unsigned int b = this->PopStack();
			unsigned int a = this->PopStack();

			unsigned int result = static_cast<unsigned int>(a == b);

			this->PushStack(result);
		}
	);*/

	this->AddOperation( OperationType::NOT,
		[this] ( Operation &op ) -> void
		{
			Word res = ! this->PopStack();

			this->PushStack(res);
		}
	);

	this->AddOperation( OperationType::EQUALS,
		[ this ] ( Operation &op ) -> void
		{
			Word lastData = this->PopStack();
			Word lastId = this->GetLastVaribleId();

			this->SetVaribleData( lastId, lastData );
		}
	);

	this->AddOperation( OperationType::LIST_ADD,
		[this] ( Operation &op ) -> void
		{
			Word data = this->PopStack();

			this->AddToList( data );
		}
	);

	this->AddOperation( OperationType::LIST_TO_START,
		[this] ( Operation &op ) -> void
		{
			this->ToStartList();
		}
	);

	this->AddOperation( OperationType::LIST_NEXT,
		[this] ( Operation &op ) -> void
		{
			this->NextList();
			//Word flag = static_cast<Word>( this->NextList() );
			//this->PushStack( flag );
		}
	);

	this->AddOperation( OperationType::LIST_GET_VALUE,
		[this] ( Operation &op ) -> void 
		{
			try
			{
				Word data = this->GetValueFromList();
				this->PushStack( data );
			}
			catch( ListNullreferenceException &e )
			{
				std::cout << e.what() << std::endl;

				throw RuntimeError();
			}
			catch( ListNotInitializedException &e )
			{
				std::cout << e.what() << std::endl;

				throw RuntimeError();
			}
		}
	);

	this->AddOperation( OperationType::VARIABLE,
		[ this ] ( Operation &op ) -> void
		{
			Word id = op.value;

			if ( this->isVariableSeted( id ) )
			{
				this->PushStack( GetVaribleData( id ) );
			}
			else
			{
				this->SetLastVaribleId( id );
			}
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

void Machine::SetVaribleData( Word varibleId, Word data )
{
	varibleData[varibleId] = data;
}

Machine::Word Machine::GetVaribleData( Word varibleId )
{
	return varibleData[varibleId];
}

void Machine::SetLastVaribleId( Word id )
{
	lastVaribleId.push_back( id );
}

Machine::Word Machine::GetLastVaribleId()
{
	Word temp = lastVaribleId[lastVaribleId.size() - 1];
	lastVaribleId.pop_back();

	return temp;
}

bool Machine::isVariableSeted( Word variableID )
{
	return !( varibleData.find( variableID ) == varibleData.end() );
}

void Machine::AddToList( Word value )
{
	myList.Add( value );
}

Machine::Word Machine::GetValueFromList()
{
	return myList.GetValue();
}

bool Machine::NextList()
{
	return myList.Next();
}

void Machine::ToStartList()
{
	myList.ToStart();
}