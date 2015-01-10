#pragma once
#include "Type.hpp"

class PointerType: public Type
{
	Type const& pointedType;
	int size;
	public:
	PointerType(Type const& pType, int size = 0);
	bool operator==(Type const&) const;
	void print(void) const;
	char getType(void) const;
	~PointerType();
	int getSize(void) const;
	bool isStaticArray(void) const;
	std::string getString(void) const;
	Type const* getPointedType(void) const;
};
