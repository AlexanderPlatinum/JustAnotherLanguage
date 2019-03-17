#include "Parser.h"

Parser::Parser()
{}

Parser::~Parser()
{}

void Parser::Initialize(const std::vector<Token> &tokens)
{
	this->tokens = tokens;
}

void Parser::Run()
{
	for (auto it = tokens.begin(); it != tokens.end(); it++)
	{
		if ( it->type == TokenType::DIGIT )
		{
			infix.push_back(Operation(OperationType::NUMBER, std::stoi(it->value)));
		}
		else if( it->type == TokenType::VARIABLE )
		{
			infix.push_back(Operation(OperationType::NUMBER, -1));
		}
		else if (it->type == TokenType::BRACKET_CLOSE)
		{
			Operation op = opStack.back();
			opStack.pop_back();

			while (op.type != OperationType::CLOSE)
			{
				infix.push_back(op);

				op = opStack.back();
				opStack.pop_back();
			}
		}
		else if (it->type == TokenType::BRACKET_OPEN)
		{
			opStack.push_back(Operation(OperationType::OPEN, 0));
		}
		else
		{
			OperationType currentOpType = getOperationType(*it);

			if (currentOpType == OperationType::NOT_FOUND) continue;

			Operation current = Operation(currentOpType, 0);
			int currentPriority = getPriority(current);

			if ( opStack.size() > 1 )
			{
				Operation opBackStack = opStack.back();
				int opBackStackPriority = getPriority(opBackStack);

				if (opBackStackPriority > currentPriority)
				{
					Operation op = opStack.back();
					opStack.pop_back();

					infix.push_back(op);
				}
			}

			opStack.push_back(current);
		}
	}

	while ( opStack.size() != 0 )
	{
		Operation op = opStack.back();
		opStack.pop_back();

		infix.push_back(op);
	}

}

std::vector<Operation> Parser::GetOperations() const
{
	return infix;
}

void Parser::PrintInfix() const
{
	for (auto it = infix.begin(); it != infix.end(); ++it)
	{
		if ( it->type == OperationType::NUMBER )
		{
			std::cout << it->value << ' ';
		}
		else
		{
			std::cout << printType(*it) << ' ';
		}
	}

	std::cout << std::endl;
}

char Parser::printType(const Operation &op) const
{
	if (op.type == OperationType::DIV)   return '/';
	if (op.type == OperationType::MUL)   return '*';
	if (op.type == OperationType::PLUS)  return '+';
	if (op.type == OperationType::MINUS) return '-';

	return ' ';
}

int Parser::getPriority(const Operation &op) const
{
	if ( op.type == OperationType::DIV ||
		 op.type == OperationType::MUL )
	{
		return 3;
	}

	if ( op.type == OperationType::PLUS ||
		 op.type == OperationType::MINUS )
	{
		return 2;
	}

	if (op.type == OperationType::CLOSE ||
		op.type == OperationType::OPEN )
	{
		return 1;
	}

	return 0;
}

OperationType Parser::getOperationType(const Token &token) const
{
	if (token.type == TokenType::OP_PLUS)     return OperationType::PLUS;
	if (token.type == TokenType::OP_MINUS)    return OperationType::MINUS;
	if (token.type == TokenType::OP_DIVISION) return OperationType::DIV;
	if (token.type == TokenType::OP_MULTIPLY) return OperationType::MUL;

	return OperationType::NOT_FOUND;
}
