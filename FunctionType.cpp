#include "FunctionType.hpp"
#include <iostream>


FunctionType::FunctionType(Type const& retType): returnType(retType)
{
}
void FunctionType::addParameter(Type const* para)
{
	parameterType.push_back(para);
}
bool FunctionType::operator==(Type const& ty) const
{
	FunctionType const* t = dynamic_cast<FunctionType const*>(&ty);
	if(t == nullptr)
		return false;
	if(t->returnType != returnType)
		return false;
	if(parameterType.size() != t->parameterType.size())
		return false;
	auto it = parameterType.begin();
	auto jt = t->parameterType.begin();
	for(; it != parameterType.end(); it++, jt++) 
		if(**it != **jt)
			return false;
	return true;
}
void FunctionType::print(void) const
{
	returnType.print();
	std::cout << " (";
	for(Type const* t : parameterType)
	{
		t->print();
		std::cout << ", ";
	}
	std::cout << ")";
}
char FunctionType::getType(void) const
{
	return FUNCTION_TYPE;
}
Type const* FunctionType::getReturnType(void) const
{
	return &returnType;
}
