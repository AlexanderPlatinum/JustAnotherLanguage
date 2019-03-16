#pragma once

#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "Token.h"
#include "Regexps.h"

class Lexer
{
private:
	std::string code;
	std::vector<Token> tokens;

	std::stringstream ss;
	Token tokenLast;

public:
	Lexer();
	~Lexer();

	void Initialize( const std::string &code );
	void Run();

	std::vector<Token> GetTokens() const;

	void PrintTokens() const;

private:
	void pushToken( char symbol, bool addSumbol = true );
	TokenType getTokenType(const std::string &str) const;
};

