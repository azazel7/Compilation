#ifndef PRIMARY_EXPRESSION_IDENTIFIER_OPERATION_HPP
#define PRIMARY_EXPRESSION_IDENTIFIER_OPERATION_HPP

#include "Node.hpp"

class PrimaryExpressionIdentifierOperation : public Node
{
	std::string name;
	char type;
	public:
		PrimaryExpressionIdentifierOperation(std::string na, char type);
		void semanticsCheck(void) const;
		Type const* getType();
		void generateCode(FILE * fd) const;
		static const char dec;
		static const char inc;
};

#endif
