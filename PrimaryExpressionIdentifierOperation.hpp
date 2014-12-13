#ifndef PRIMARY_EXPRESSION_IDENTIFIER_OPERATION_HPP
#define PRIMARY_EXPRESSION_IDENTIFIER_OPERATION_HPP

#include "Node.hpp"

class PrimaryExpressionIdentifierOperation : public Node
{
	std::string name;
	public:
		PrimaryExpressionIdentifierOperation(std::string na);
		void semanticsCheck(void) const;
		Type* getType();
};

#endif
