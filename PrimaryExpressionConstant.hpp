#ifndef PRIMARY_EXPRESSION_CONSTANT_HPP
#define PRIMARY_EXPRESSION_CONSTANT_HPP 

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
		void semanticsCheck(void) const;
		Type* getType();
		~PrimaryExpressionConstant();

};
#endif

