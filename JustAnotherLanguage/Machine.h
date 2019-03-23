#pragma once

#include <map>
#include <vector>
#include <functional>

#include "Operation.h"

class Machine
{
private:
	unsigned int pc;

	Programm program;
	std::vector<unsigned int> stack;

public:
	Machine() = default;
	~Machine() = default;

	void SetProgramm( const Programm &program );
	void AddOperation();
	void Run();
	void Reset();
};