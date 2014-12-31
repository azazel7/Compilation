#pragma once

#include "Node.hpp"
#define CONSTANT_FLOAT 'f'
#define CONSTANT_INT 'i'

class Type;

class PrimaryExpressionConstant: public Node
{
	std::string value;
	Type* type;
	public:
		PrimaryExpressionConstant(std::string value, char type);
		Type const* getType();
		void generateCode(FILE * fd) const;
		~PrimaryExpressionConstant();

};
