#pragma once

#include <regex>

const std::regex REGEX_VARIABLE("[A-z]+");
const std::regex REGEX_DIGIT("0|[1-9][0-9]*");
const std::regex REGEX_ASSIGN_OP(":=");
const std::regex REGEX_WHILE("while");
const std::regex REGEX_IF("if");
const std::regex REGEX_DEF("def");

const char REGEX_OP_COLON = ':';
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