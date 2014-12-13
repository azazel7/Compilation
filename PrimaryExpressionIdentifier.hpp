#ifndef PRIMARY_EXPRESSION_IDENTIFIER_HPP
#define PRIMARY_EXPRESSION_IDENTIFIER_HPP

#include "Node.hpp"

class PrimaryExpressionIdentifier: public Node
{
	std::string name;
	public:
		PrimaryExpressionIdentifier(std::string name);
		void semanticsCheck(void) const;
		Type* getType();

};
#endif
