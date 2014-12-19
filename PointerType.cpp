#include "PointerType.hpp"
#include <iostream>

PointerType::PointerType(Type const& pType, int size):pointedType(pType), size(size)
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
int PointerType::getSize(void) const
{
	if(size == 0)
		return sizeof(void*);
	return size*pointedType.getSize();
}
bool PointerType::isStaticArray(void) const
{
	return size == 0;
}
std::string PointerType::getString(void) const
{
	return "*" + pointedType.getString();
}
Type const* PointerType::getPointedType(void) const
{
	return &pointedType;
}
