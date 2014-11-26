#ifndef PRIMITIVE_TYPE_HPP 
#define PRIMITIVE_TYPE_HPP 
#include <string>
#include "Type.hpp"

class PrimitiveType : public Type
{
	std::string nameType;
	public:
	PrimitiveType(std::string type);
	bool operator==(Type const&) const;
};
#endif

