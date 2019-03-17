#include "Lexer.h"

void Lexer::Initialize( const std::string &code )
{
	this->code = code;
}

void Lexer::Run()
{
	for (size_t i = 0; i < code.size(); i++)
	{
		char symbol = code[i];

		if (symbol == ' ' || symbol == '\t' || symbol == '\n')
		{
			if ( tokenLast.type == TokenType::DEF ||
				 tokenLast.type == TokenType::FOR ||
				 tokenLast.type == TokenType::IN  ||
				 tokenLast.type == TokenType::VARIABLE )
			{
				pushToken(symbol, false );
			}

			continue;
		}

		ss << symbol;
		TokenType type = getTokenType(ss.str());

		if ( type == TokenType::NO_MATCH )
		{
			pushToken(symbol);

			type = getTokenType(ss.str());
		}
		
		tokenLast.type = type;
		tokenLast.value = ss.str();
	}

	tokens.push_back(tokenLast);
}

std::vector<Token> Lexer::GetTokens() const
{
	return this->tokens;
}

void Lexer::PrintTokens() const
{
	for (auto it = tokens.begin(); it != tokens.end(); ++it)
	{
		std::cout << "Token: " << std::endl;
		std::cout << '\t' << "Type := " << static_cast<int>( it->type ) << std::endl;
		std::cout << '\t' << "Value := " << it->value << std::endl;
	}
}

void Lexer::pushToken(char symbol, bool addSymbol)
{
	tokens.push_back(tokenLast);

	ss.str(std::string());
	if( addSymbol == true ) ss << symbol;
}

TokenType Lexer::getTokenType( const std::string &str ) const
{
	if ( str.size() == 1 )
	{
		if (str[0] == REGEX_OP_COMMA)         return TokenType::OP_COMMA;
		if (str[0] == REGEX_OP_COLON)         return TokenType::OP_COLON;
		if (str[0] == REGEX_OP_SEMICONON)     return TokenType::OP_SEMICONON;

		if (str[0] == REGEX_OP_PLUS)          return TokenType::OP_PLUS;
		if (str[0] == REGEX_OP_MINUS)         return TokenType::OP_MINUS;
		if (str[0] == REGEX_OP_MULTIPLY)      return TokenType::OP_MULTIPLY;
		if (str[0] == REGEX_OP_DIVISION)      return TokenType::OP_DIVISION;

		if (str[0] == REGEX_OP_EQUALS)        return TokenType::OP_EQUALS;
		if (str[0] == REGEX_OP_NOT)           return TokenType::OP_NOT;

		if (str[0] == REGEX_OP_LESS)          return TokenType::OP_LESS;
		if (str[0] == REGEX_OP_BIGGEST)       return TokenType::OP_BIGGEST;

		if (str[0] == REGEX_BRACKETS_OPEN)    return TokenType::BRACKETS_OPEN;
		if (str[0] == REGEX_BRACKETS_CLOSE)   return TokenType::BRACKETS_CLOSE;

		if (str[0] == REGEX_BRACKETS_F_OPEN)  return TokenType::BRACKETS_F_OPEN;
		if (str[0] == REGEX_BRACKETS_F_CLOSE) return TokenType::BRACKETS_F_CLOSE;
	}

	try
	{
		int count = 0;
		TokenType type;

		if (std::regex_match(str, REGEX_ASSIGN_OP))
		{
			count++;
			type = TokenType::ASSIGN_OP;
		}

		if (std::regex_match(str, REGEX_DIGIT))
		{
			count++;
			type = TokenType::DIGIT;
		}

		if (std::regex_match(str, REGEX_WHILE))
		{
			count++;
			type = TokenType::WHILE;
		}
		else if (std::regex_match(str, REGEX_IF))
		{
			count++;
			type = TokenType::IF;
		}
		else if (std::regex_match(str, REGEX_DEF))
		{
			count++;
			type = TokenType::DEF;
		}
		else if (std::regex_match(str, REGEX_RETURN))
		{
			count++;
			type = TokenType::RETURN;
		} 
		else if (std::regex_match(str, REGEX_FOR))
		{
			count++;
			type = TokenType::FOR;
		}
		else if (std::regex_match(str, REGEX_IN))
		{
			count++;
			type = TokenType::IN;
		}
		else if (std::regex_match(str, REGEX_ELSE))
		{
			count++;
			type = TokenType::ELSE;
		}
		else
		{
			if (std::regex_match(str, REGEX_VARIABLE))
			{
				count++;
				type = TokenType::VARIABLE;
			}
		}

		if (count == 1) return type;
		if (count == 0) return TokenType::NO_MATCH;
	}
	catch ( std::regex_error &e )
	{
		std::cout << e.what() << std::endl;
	}

	return TokenType::ALSO_NEED;
}
