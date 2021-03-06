#pragma once
#include <string>
#include "Type.hpp"

class PrimitiveType : public Type
{
	std::string nameType;
	public:
	PrimitiveType(std::string type);
	void print(void) const;
	bool operator==(Type const&) const;
	char getType(void) const;
	static const std::string int_type;
	static const std::string float_type;
	static const std::string void_type;
	int getSize() const;
	std::string getString(void) const;
};
