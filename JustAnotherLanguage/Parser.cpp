#include "Parser.h"

Parser::Parser() :
	countOfVariables(0),
	currentLevel( 0 )
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
			int id = getVariableIdByName( it->value );
			infix.push_back(Operation(OperationType::VARIABLE, id));
		}
		else if (it->type == TokenType::BRACKETS_CLOSE)
		{
			Operation op = opStack.back();
			opStack.pop_back();

			while (op.type != OperationType::OPEN)
			{
				infix.push_back(op);

				op = opStack.back();
				opStack.pop_back();
			}

			if (isNeedPutGotoFlag())
			{
				infix.push_back(Operation(OperationType::NUMBER, NEED_CALCULATE));
				infix.push_back(Operation(OperationType::GOTO_F, 0));
			}
		}
		else if (it->type == TokenType::BRACKETS_OPEN)
		{
			opStack.push_back(Operation(OperationType::OPEN, 0));
		}
		else if ( it->type == TokenType::IF )
		{
			levels[currentLevel + 1] = GotoType::Next;
		}
		else if (it->type == TokenType::WHILE)
		{
			levels[currentLevel + 1] = GotoType::EveryWhere;
			gotoLines.push_back(infix.size());
		}
		else if ( it->type == TokenType::BRACKETS_F_OPEN )
		{
			currentLevel++;
		}
		else if (it->type == TokenType::BRACKETS_F_CLOSE)
		{
			copyFromOpStackToInfix();
			prepairGoto();

			currentLevel--;
			if (currentLevel <= 0)
			{
				levels.clear();
			}
		}
		else
		{
			OperationType currentOpType = getOperationType(*it);

			if (currentOpType == OperationType::NOT_FOUND) continue;
			prepairMathOperands(currentOpType);
		}
	}
	
	putGoto();
}

std::vector<Operation> Parser::GetOperations() const
{
	return infix;
}

void Parser::PrintInfix() const
{
	for (auto it = infix.begin(); it != infix.end(); ++it)
	{
		if (it->type == OperationType::NUMBER)
		{
			std::cout << it->value << ' ';
		}
		else if (it->type == OperationType::VARIABLE)
		{
			std::cout << "( var with id " << it->value << " ) ";
		}
		else if ( it->type == OperationType::GOTO_F)
		{
			std::cout << "F! ";
		}
		else if (it->type == OperationType::GOTO)
		{
			std::cout << "! ";
		}
		else
		{
			std::cout << printType(*it) << ' ';
		}
	}

	std::cout << std::endl;
}

void Parser::copyFromOpStackToInfix()
{
	while (opStack.size() != 0)
	{
		Operation op = opStack.back();
		opStack.pop_back();

		infix.push_back(op);
	}
}

void Parser::prepairMathOperands(const OperationType &currentOpType)
{
	Operation current = Operation(currentOpType, 0);
	int currentPriority = getPriority(current);

	if (opStack.size() > 1)
	{
		Operation opBackStack = opStack.back();
		int opBackStackPriority = getPriority(opBackStack);

		if (opBackStackPriority >= currentPriority)
		{
			Operation op = opStack.back();
			opStack.pop_back();

			infix.push_back(op);
		}
	}

	opStack.push_back(current);
}

void Parser::prepairGoto()
{
	GotoType type = levels[currentLevel];

	if (type == GotoType::Prev)
	{
		infix.push_back(Operation(OperationType::NUMBER, NEED_CALCULATE));
		infix.push_back(Operation(OperationType::GOTO, 0));
	}

	if (type == GotoType::Next)
	{
		gotoLines.push_back( infix.size() );
	}

	if (type == GotoType::EveryWhere)
	{
		infix.push_back(Operation(OperationType::NUMBER, NEED_CALCULATE));
		infix.push_back(Operation(OperationType::GOTO, 0));

		gotoLines.push_back(infix.size());
	}

	levels[currentLevel] = GotoType::NoNeed;
}

void Parser::putGoto()
{
	int line = 0;
	for ( auto it = infix.begin(); it != infix.end(); ++it )
	{
		if ( it->type  == OperationType::NUMBER &&
			 it->value == NEED_CALCULATE )
		{
			it->value = gotoLines[line];
			line++;
		}
	}
}

bool Parser::isNeedPutGotoFlag()
{
	if (levels.find( currentLevel + 1 ) == levels.end())
	{
		return false;
	}

	if (levels[currentLevel + 1] == GotoType::NoNeed)
	{
		return false;
	}

	return true;
}

int Parser::getVariableIdByName(const std::string &name)
{
	int id = 0;

	if ( variables.find( name ) == variables.end() )
	{
		variables[name] = id = countOfVariables;
		countOfVariables++;
	}
	else
	{
		id = variables[name];
	}

	return id;
}

char Parser::printType(const Operation &op) const
{
	if (op.type == OperationType::DIV)     return '/';
	if (op.type == OperationType::MUL)     return '*';
	if (op.type == OperationType::PLUS)    return '+';
	if (op.type == OperationType::MINUS)   return '-';
	if (op.type == OperationType::EQUALS)  return '=';
	if (op.type == OperationType::LESS)    return '<';
	if (op.type == OperationType::BIGGEST) return '>';
	if (op.type == OperationType::NOT)     return '!';

	return ' ';
}

int Parser::getPriority(const Operation &op) const
{
	if ( op.type == OperationType::GOTO_F)
	{
		return 10;
	}

	if ( op.type == OperationType::DIV ||
		 op.type == OperationType::MUL )
	{
		return 9;
	}

	if ( op.type == OperationType::PLUS ||
		 op.type == OperationType::MINUS )
	{
		return 8;
	}

	if ( op.type == OperationType::EQUALS ||
		 op.type == OperationType::LESS   ||
		 op.type == OperationType::BIGGEST   )
	{
		return 6;
	}

	if ( op.type == OperationType::NOT )
	{
		return 7;
	}

	if ( op.type == OperationType::CLOSE ||
		 op.type == OperationType::OPEN  )
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
	if (token.type == TokenType::OP_EQUALS)   return OperationType::EQUALS;
	if (token.type == TokenType::OP_LESS)     return OperationType::LESS;
	if (token.type == TokenType::OP_BIGGEST)  return OperationType::BIGGEST;
	if (token.type == TokenType::OP_NOT)      return OperationType::NOT;

	return OperationType::NOT_FOUND;
}
