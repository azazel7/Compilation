#ifndef TYPE_OPERATION_CONVERSION_HPP 
#define TYPE_OPERATION_CONVERSION_HPP 

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
		static Type* getTypeOperation(char operation, Type& t1, Type& t2);
};
#endif
