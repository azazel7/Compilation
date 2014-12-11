#ifndef ADDITIVE_EXPRESSION_HPP
#define ADDITIVE_EXPRESSION_HPP
#include "Node.hpp"

class AdditiveExpression : public Node
{
	char type;
	Node& right;
	Node& left;
	public:
		AdditiveExpression(Node& r, Node& l, char t);
		void semanticsCheck(void) const;
		Type* getType();
	static const char sub;
	static const char add;
};
#endif
