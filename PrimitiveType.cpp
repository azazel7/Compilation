#include "PrimitiveType.hpp"
#include <iostream>

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