#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "Token.h"
#include "Operation.h"

const int NEED_CALCULATE = -1;

class Parser
{
private:
	int countOfVariables;
	std::map<std::string, int> variables;

	std::vector<Token> tokens;
	std::vector<Operation> infix;
	std::vector<Operation> opStack;

	std::vector<int> gotoLines;
	bool needCloseGoto;

public:
	Parser();

	void Initialize(const std::vector<Token> &tokens);
	void Run();

	std::vector<Operation> GetOperations() const;
	void PrintInfix() const;

private:
	void copyFromOpStackToInfix();
	void prepairMathOperands(const OperationType &currentOpType);
	void putGoto();

	int getVariableIdByName(const std::string &name);

	int getPriority(const Operation &op) const;
	OperationType getOperationType( const Token &token ) const;
	
	char printType( const Operation &op ) const;
};
