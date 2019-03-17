#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Token.h"
#include "Operation.h"

class Parser
{
private:
	std::vector<Token> tokens;
	std::vector<Operation> infix;
	std::vector<Operation> opStack;

public:
	Parser() = default;

	void Initialize(const std::vector<Token> &tokens);
	void Run();

	std::vector<Operation> GetOperations() const;
	void PrintInfix() const;

private:
	int getPriority(const Operation &op) const;
	OperationType getOperationType( const Token &token ) const;
	
	char printType( const Operation &op ) const;
};

