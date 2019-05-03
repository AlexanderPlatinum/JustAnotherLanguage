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
		else if ( it->type == TokenType::BRACKETS_CLOSE )
		{
			bracketsClose();
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
		else if (it->type == TokenType::BRACKETS_F_CLOSE )
		{
			currentLevel--;
			if (currentLevel <= 0)
			{
				levels.clear();
			}
		}
		else if ( it->type == TokenType::OP_SEMICONON )
		{
			copyFromOpStackToInfix();
			prepairGoto();
		}
		else if ( it->type == TokenType::PRINT )
		{
			opStack.push_back(Operation(OperationType::PRINT, 0));
		}
		else if ( it->type == TokenType::LIST_ADD )
		{
			opStack.push_back(Operation(OperationType::LIST_ADD, 0));
		}
		else if ( it->type == TokenType::LIST_TO_START )
		{
			opStack.push_back(Operation(OperationType::LIST_TO_START, 0));
		}
		else if ( it->type == TokenType::LIST_NEXT )
		{
			opStack.push_back(Operation(OperationType::LIST_NEXT, 0));
		}
		else if ( it->type == TokenType::LIST_GET_VALUE )
		{
			opStack.push_back(Operation(OperationType::LIST_GET_VALUE, 0));
		} 
		else if ( it->type == TokenType::HASHSET_ADD )
		{
			opStack.push_back(Operation(OperationType::HASHSET_ADD, 0));
		}
		else if ( it->type == TokenType::HASHSET_GET )
		{
			opStack.push_back(Operation(OperationType::HASHSET_GET, 0));
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

void Parser::AssemblyListing(const std::string &fileName) const
{
	std::ofstream fout( fileName );

	for (auto it = infix.begin(); it != infix.end(); ++it)
	{
		if (it->type == OperationType::NUMBER   ||
			it->type == OperationType::VARIABLE )
		{
			fout << getNameOfOperand(*it) << it->value << std::endl;
		}
		else
		{
			fout << getNameOfOperand(*it) << std::endl;
		}
	}

	fout.close();
}

void Parser::copyFromOpStackToInfix()
{
	//std::reverse( opStack.begin(), opStack.end() );

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

		gotoLines.push_back(infix.size() );
	}

	levels[currentLevel] = GotoType::NoNeed;
}

void Parser::putGoto()
{
	int line = gotoLines.size() - 1;
	for ( auto it = infix.begin(); it != infix.end(); ++it )
	{
		if ( it->type  == OperationType::NUMBER &&
			 it->value == NEED_CALCULATE )
		{
			it->value = ( gotoLines[line] == 0 ) ? 0 : gotoLines[line] - 1;
			line--;
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
	if (op.type == OperationType::DIV)            return '/';
	if (op.type == OperationType::MUL)            return '*';
	if (op.type == OperationType::PLUS)           return '+';
	if (op.type == OperationType::MINUS)          return '-';
	if (op.type == OperationType::EQUALS)         return '=';
	if (op.type == OperationType::LESS)           return '<';
	if (op.type == OperationType::BIGGEST)        return '>';
	if (op.type == OperationType::NOT)            return '!';
	if (op.type == OperationType::PRINT)          return 'p';
	if (op.type == OperationType::LIST_ADD)       return 'A';
	if (op.type == OperationType::LIST_GET_VALUE) return 'V';
	if (op.type == OperationType::LIST_NEXT)      return 'N';
	if (op.type == OperationType::LIST_TO_START)  return 'S';
	if (op.type == OperationType::HASHSET_ADD)    return 'H';
	if (op.type == OperationType::HASHSET_GET)    return 'h';

	return ' ';
}

int Parser::getPriority(const Operation &op) const
{

	if (op.type == OperationType::GOTO_F )
	{
		return 11;
	}

	if ( op.type == OperationType::DIV ||
		 op.type == OperationType::MUL )
	{
		return 9;
	}

	if ( op.type == OperationType::PLUS  ||
		 op.type == OperationType::MINUS )
	{
		return 8;
	}

	if ( op.type == OperationType::LESS    ||
		 op.type == OperationType::BIGGEST )
	{
		return 7;
	}

	if ( op.type == OperationType::NOT )
	{
		return 6;
	}

	if ( op.type == OperationType::CLOSE ||
		 op.type == OperationType::OPEN  ||
		 op.type == OperationType::PRINT ||
		 op.type == OperationType::LIST_ADD       ||
		 op.type == OperationType::LIST_TO_START  ||
		 op.type == OperationType::LIST_NEXT      ||
		 op.type == OperationType::LIST_GET_VALUE ||
		 op.type == OperationType::HASHSET_ADD    ||
		 op.type == OperationType::HASHSET_GET      )
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
	if (token.type == TokenType::PRINT)       return OperationType::PRINT;

	return OperationType::NOT_FOUND;
}

std::string Parser::getNameOfOperand(const Operation &op) const
{
	if (op.type == OperationType::NUMBER)         return "push #";
	if (op.type == OperationType::VARIABLE)       return "push @";
	if (op.type == OperationType::PLUS)           return "add";
	if (op.type == OperationType::MINUS)          return "sub";
	if (op.type == OperationType::MUL)            return "mul";
	if (op.type == OperationType::DIV)            return "div";
	if (op.type == OperationType::LESS)           return "comp_less";
	if (op.type == OperationType::BIGGEST)        return "comp_bigg";
	if (op.type == OperationType::EQUALS)         return "comp_equa";
	if (op.type == OperationType::GOTO_F)         return "jn";
	if (op.type == OperationType::GOTO)           return "jmp";
	if (op.type == OperationType::PRINT)          return "print";
	if (op.type == OperationType::LIST_ADD)       return "list_add";
	if (op.type == OperationType::LIST_GET_VALUE) return "list_get_value";
	if (op.type == OperationType::LIST_NEXT)      return "list_next";
	if (op.type == OperationType::LIST_TO_START)  return "list_to_start";
	if (op.type == OperationType::HASHSET_ADD)    return "hash_set_add";
	if (op.type == OperationType::HASHSET_GET)    return "hash_set_get";

	return "nop";
}

void Parser::bracketsClose()
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
