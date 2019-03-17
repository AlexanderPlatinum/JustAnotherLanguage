#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Token.h"

enum class OperationType
{
	NUMBER,
	PLUS,
	MINUS,
	MUL,
	DIV,
	LESS,
	BIGGEST,
	EQUALS,
	OPEN,
	CLOSE,
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

class Parser
{
private:
	std::vector<Token> tokens;
	std::vector<Operation> infix;
	std::vector<Operation> opStack;

public:
	Parser();
	~Parser();

	void Initialize(const std::vector<Token> &tokens);
	void Run();

	std::vector<Operation> GetOperations() const;
	void PrintInfix() const;

private:
	int getPriority(const Operation &op) const;
	OperationType getOperationType( const Token &token ) const;
	
	char printType( const Operation &op ) const;
};

