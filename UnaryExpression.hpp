#ifndef UNARY_EXPRESSION_HPP 
#define UNARY_EXPRESSION_HPP 
#include "Node.hpp"

class UnaryExpression: public Node
{
	Node& expression;
	public:
		UnaryExpression(Node& l);
		void semanticsCheck(void) const;
		Type const* getType();
};
#endif

