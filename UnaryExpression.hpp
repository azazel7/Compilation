#ifndef UNARY_EXPRESSION_HPP 
#define UNARY_EXPRESSION_HPP 
#include "Node.hpp"

class UnaryExpression: public Node
{
	Node& expression;
	char type;
	public:
		UnaryExpression(Node& l);
		void semanticsCheck(void) const;
		Type const* getType(); //TODO change the type for ! which whiche return an INT
		void generateCode(FILE * fd) const;
	static const char neg;
	static const char no;
};
#endif

