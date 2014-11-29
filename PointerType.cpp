#include "PointerType.hpp"
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

