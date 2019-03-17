#pragma once

enum class OperationType
{
	NUMBER,
	VARIABLE,
	PLUS,
	MINUS,
	MUL,
	DIV,
	LESS,
	BIGGEST,
	EQUALS,
	OPEN,
	CLOSE,
	GOTO_F,
	GOTO,
	NOT,
	NOT_FOUND
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
