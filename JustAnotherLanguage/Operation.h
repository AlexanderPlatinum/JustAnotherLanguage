#pragma once

#include <vector>

enum class OperationType
{
	NUMBER,         // +
	VARIABLE,       // + 
	PLUS,           // +
	MINUS,          // +
	MUL,            // +
	DIV,            // +
	LESS,           // +
	BIGGEST,        // +
	EQUALS,         // +
	OPEN,           // ?
	CLOSE,          // ?
	GOTO_F,         // +
	GOTO,           // +
	NOT,            // +
	PRINT,          // +
	LIST_ADD,       // +
	LIST_NEXT,      // + 
	LIST_TO_START,  // +
	LIST_GET_VALUE, // +
	HASHMAP_ADD,    // +
	HASHMAP_GET,    // +
	HASHSET_ADD,
	HASHSET_NEXT,
	HASHSET_TO_START,
	HASHSET_GET_VALUE,
	NOT_FOUND       // +
};

enum class GotoType
{
	NoNeed,
	Prev,
	Next,
	EveryWhere
};

struct Operation
{
	OperationType type;
	int value;

	Operation() = default;

	Operation(OperationType _type, int _value)
		: type(_type), value(_value)
	{}
};

using Programm = std::vector<Operation>;
