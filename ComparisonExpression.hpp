#ifndef COMPARISON_EXPRESSION_HPP
#define COMPARISON_EXPRESSION_HPP
#include "Node.hpp"

class ComparisonExpression : public Node
{
	Type* type;
	Node& right;
	Node& left;
	public:
		ComparisonExpression(Node& right, Node &left);
		void semanticsCheck(void) const;
		Type* getType();
};
#endif
