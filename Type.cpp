#include "Type.hpp"

bool Type::operator!=(Type const& t) const
{
	return !(t == *this);
}
