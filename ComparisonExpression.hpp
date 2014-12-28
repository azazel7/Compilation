#ifndef COMPARISON_EXPRESSION_HPP
#define COMPARISON_EXPRESSION_HPP
#include "Node.hpp"

#define COMPARISON_LE 1
#define COMPARISON_L 2
#define COMPARISON_GE 3
#define COMPARISON_G 4
#define COMPARISON_EQ 5
#define COMPARISON_NE 6

class ComparisonExpression : public Node
{
	Type* type;
	Node& right;
	Node& left;
	char typeOp;
	public:
		ComparisonExpression(Node& right, Node &left, char t);
		void semanticsCheck(void) const;
		Type const* getType();
		void generateCode(FILE * fd) const;
};
#endif
