#ifndef MULTIPLICATIVE_EXPRESSION_HPP
#define MULTIPLICATIVE_EXPRESSION_HPP
#include "Node.hpp"

class MultiplicativeExpression : public Node
{
	Node& right;
	Node& left;
	public:
		MultiplicativeExpression(Node& r, Node& l);
		void semanticsCheck(void) const;
		Type const* getType();
		void generateCode(FILE * fd) const;
};
#endif
