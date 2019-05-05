#pragma once

#include <string>

enum class TokenType
{
	VARIABLE = 1,      // +
	DIGIT,             // +
	ASSIGN_OP,         // -
	OP_COMMA,          // -
	OP_COLON,          // -
	OP_SEMICONON,      // -
	OP_PLUS,           // +
	OP_MINUS,          // +
	OP_MULTIPLY,       // +
	OP_DIVISION,       // +
	OP_EQUALS,         // +
	OP_NOT,            // +
	OP_LESS,           // +
	OP_BIGGEST,        // +
	DEF,               // -
	RETURN,            // -
	BRACKETS_CLOSE,    // +
	BRACKETS_OPEN,     // +
	BRACKETS_F_OPEN,   // +
	BRACKETS_F_CLOSE,  // +
	WHILE,             // +
	IF,                // +
	ELSE,              // -
	FOR,               // -
	IN,                // -
	PRINT,             // +
	LIST_ADD,          // +
	LIST_NEXT,         // +
	LIST_TO_START,     // +
	LIST_GET_VALUE,    // +
	HASHMAP_ADD,       // +
	HASHMAP_GET,       // +
	HASHSET_ADD,       // +
	HASHSET_NEXT,      // +
	HASHSET_TO_START,  // +
	HASHSET_GET_VALUE, // +
	NO_MATCH,
	ALSO_NEED
};

struct Token
{
	TokenType type;
	std::string value;
};
