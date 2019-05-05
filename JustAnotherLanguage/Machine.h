#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <exception>
#include <functional>

#include "List.h"
#include "HashSet.h"
#include "HashMap.h"

#include "Operation.h"

class RuntimeError : public std::exception
{
public:
	virtual char const* what() const noexcept
	{
		return "Runtime error in Machine::Run()";
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
	HashSet <Word>       myHashSet;
	HashMap <Word, Word> myHashMap;

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

	// List
	void AddToList( Word value );
	Word GetValueFromList();
	bool NextList();
	void ToStartList();

	// Hash Map
	void AddToHashMap( Word index, Word value );
	Word GetFromHashMap( Word index );

	// Hash Set
	void AddToHashSet( Word value );
	Word GetValueFromHashSet();
	bool NextHashSet();
	void ToStartHashSet();
};
