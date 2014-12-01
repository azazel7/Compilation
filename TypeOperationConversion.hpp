#ifndef TYPE_OPERATION_CONVERSION_HPP 
#define TYPE_OPERATION_CONVERSION_HPP 

#include <map>

class Type;

#define OPERATION_ADD '+'
#define OPERATION_SUB '+' //Same as OPERATION_SUB
#define OPERATION_BY '*'
#define OPERATION_DIV '/'
#define OPERATION_DEC 'a'
#define OPERATION_INC 'a'

class TypeOperationConversion
{
	public:
		static Type* getTypeOperation(char operation, Type& t1, Type& t2);
};
#endif
