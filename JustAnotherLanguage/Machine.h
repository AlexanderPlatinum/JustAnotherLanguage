#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <exception>
#include <functional>

#include "List.h"
#include "HashSet.h"
#include "Operation.h"

class RuntimeError : public std::exception
{
public:
	virtual char const* what() const noexcept
	{
		return "Unknow Operation in Machine::Run()";
	}
};

class Machine
{
private:

	using Stack = std::vector<unsigned int>;
	using Word = unsigned int;

	Word pc;
	Programm program;
	Stack stack;

	std::map<OperationType, std::function<void( Operation &op)>> operations;
	std::map<Word, Word> varibleData;

	std::vector<Word> lastVaribleId;

	List    <Word>       myList;
	HashSet <Word, Word> myHashSet;

public:
	Machine();
	~Machine() = default;

	void SetProgramm( const Programm &program );
	void Run();
	void Reset();

	void AddOperation(const OperationType &op,
				      std::function<void(Operation &op)> func);

	void PushStack( Word word );
	Word PopStack();
	void SetPC( Word _pc );

	void SetVaribleData( Word varibleId, Word data );
	Word GetVaribleData( Word varivleId );

	bool isVariableSeted( Word variableID );

	void SetLastVaribleId( Word id );
	Word GetLastVaribleId();

	void AddToList( Word value );
	Word GetValueFromList();
	bool NextList();
	void ToStartList();

	void AddToHashSet( Word index, Word value );
	Word GetFromHashSet( Word index );
};