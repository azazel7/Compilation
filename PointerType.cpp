#include "PointerType.hpp"
#include <iostream>

PointerType::PointerType(Type & pType):pointedType(pType)
{
}

bool PointerType::operator==(Type const& ty) const
{
	PointerType const* t = dynamic_cast<PointerType const*>(&ty);
	if(t == nullptr)
		return false;
	return pointedType == t->pointedType;
}
void PointerType::print(void) const
{
	std::cout << "*";
	pointedType.print();
}

char PointerType::getType(void)
{
	return POINTER_TYPE;
}
