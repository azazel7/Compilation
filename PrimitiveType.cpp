#include "PrimitiveType.hpp"
#include <iostream>

const std::string PrimitiveType::int_type = "INT";
const std::string PrimitiveType::float_type = "FLOAT";
const std::string PrimitiveType::void_type = "VOID";

PrimitiveType::PrimitiveType(std::string type)
{
	nameType = type;
}
bool PrimitiveType::operator==(Type const& ty) const 
{
	PrimitiveType const* t = dynamic_cast<PrimitiveType const*>(&ty);
	if(t == nullptr)
		return false;
	return (nameType == t->nameType);
}
void PrimitiveType::print(void) const
{
	std::cout << nameType;
}
char PrimitiveType::getType(void)
{
	return INT_TYPE;
}
