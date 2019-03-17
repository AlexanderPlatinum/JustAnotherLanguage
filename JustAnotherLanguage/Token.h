#pragma once

#include <string>

enum class TokenType
{
	VARIABLE = 1,     // +
	DIGIT,            // +
	ASSIGN_OP,        // -
	OP_COMMA,         // -
	OP_COLON,         // -
	OP_SEMICONON,     // -
	OP_PLUS,          // +
	OP_MINUS,         // +
	OP_MULTIPLY,      // +
	OP_DIVISION,      // +
	OP_EQUALS,        // +
	OP_NOT,           // +
	OP_LESS,          // +
	OP_BIGGEST,       // +
	DEF,              // -
	RETURN,           // -
	BRACKETS_CLOSE,   // +
	BRACKETS_OPEN,    // +
	BRACKETS_F_OPEN,  // +
	BRACKETS_F_CLOSE, // +
	WHILE,            // +
	IF,               // +
	ELSE,             // -
	FOR,              // -
	IN,               // -
	NO_MATCH,
	ALSO_NEED
};

struct Token
{
	TokenType type;
	std::string value;
};
