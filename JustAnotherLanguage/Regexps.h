#pragma once

#include <regex>

const std::regex REGEX_VARIABLE    ("[A-z]+");
const std::regex REGEX_DIGIT       ("0|[1-9][0-9]*");
const std::regex REGEX_ASSIGN_OP   (":=");
const std::regex REGEX_WHILE       ("while");
const std::regex REGEX_IF          ("if");
const std::regex REGEX_FOR         ("for");
const std::regex REGEX_IN          ("in");
const std::regex REGEX_DEF         ("def");
const std::regex REGEX_RETURN      ("return");
const std::regex REGEX_ELSE        ("else");
const std::regex REGEX_PRINT       ( "print" );
const std::regex REGEX_ADD         ( "list_add" );
const std::regex REGEX_NEXT        ( "list_next" );
const std::regex REGEX_TO_START    ( "list_to_start" );
const std::regex REGEX_GET_VALUE   ( "list_get_value" );
const std::regex REGEX_ADD_HASHMAP ( "hash_map_add" );
const std::regex REGEX_GET_HASHMAP ( "hash_map_get" );

const char REGEX_OP_COMMA = ',';
const char REGEX_OP_COLON = ':';
const char REGEX_OP_SEMICONON = ';';
const char REGEX_OP_PLUS = '+';
const char REGEX_OP_MINUS = '-';
const char REGEX_OP_MULTIPLY = '*';
const char REGEX_OP_DIVISION = '\\';
const char REGEX_OP_EQUALS = '=';
const char REGEX_OP_NOT = '!';
const char REGEX_OP_LESS = '<';
const char REGEX_OP_BIGGEST = '>';

const char REGEX_BRACKETS_OPEN = '(';
const char REGEX_BRACKETS_CLOSE = ')';

const char REGEX_BRACKETS_F_OPEN = '{';
const char REGEX_BRACKETS_F_CLOSE = '}';
