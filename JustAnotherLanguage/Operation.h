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
	GOTO,
	NOT,
	NOT_FOUND
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
