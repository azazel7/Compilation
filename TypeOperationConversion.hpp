#pragma once
#include <map>

#include "Type.hpp"

#define OPERATION_ADD '+'
#define OPERATION_SUB '+' //Same as OPERATION_SUB
#define OPERATION_BY '*'
#define OPERATION_DIV '/'
#define OPERATION_DEC 'a'
#define OPERATION_INC 'a'
#define OPERATION_MINUS 'm'
#define OPERATION_DIF '!'

class TypeOperationConversion
{
	static std::map<char, std::map<char, std::map<char, char>>> table;
	public:
		static void initTable(void);
		static Type const* getTypeOperation(char operation, Type const& t1, Type const& t2);
};
