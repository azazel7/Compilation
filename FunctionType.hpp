#ifndef FUNCTION_TYPE_HPP 
#define FUNCTION_TYPE_HPP 
#include <string>
#include <list>
#include "Type.hpp"

class FunctionType: public Type
{
	Type const& returnType;
	std::list<Type const*> parameterType;	
	public:
	FunctionType(Type const& returnType);
	void addParameter(Type const* para);
	bool operator==(Type const&) const;
	void print(void) const;
	char getType(void) const;
	Type const* getReturnType(void) const;
	int getSize() const;
	std::string getString(void) const;
};
#endif

