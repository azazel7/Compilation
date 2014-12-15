#include "PointerType.hpp"
#include <iostream>

PointerType::PointerType(Type const& pType):pointedType(pType)
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

char PointerType::getType(void) const
{
	return POINTER_TYPE;
}

PointerType::~PointerType()
{
	//TODO not sure if it's good to delete this way
	delete &pointedType;
}
