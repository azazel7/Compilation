#ifndef POINTER_TYPE_HPP 
#define POINTER_TYPE_HPP 

#include "Type.hpp"

class PointerType: public Type
{
	Type& pointedType;
	public:
	PointerType(Type & pType);
	bool operator==(Type const&) const;
	void print(void) const;
	char getType(void);
};
#endif

