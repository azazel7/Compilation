#ifndef FUNCTION_TYPE_HPP 
#define FUNCTION_TYPE_HPP 
#include <string>
#include <list>
#include "Type.hpp"

class FunctionType: public Type
{
	Type const& returnType;
	std::list<Type*> parameterType;	
	public:
	FunctionType(Type const& returnType);
	void addParameter(Type* para);
	bool operator==(Type const&) const;
	void print(void) const;
	char getType(void);
};
#endif

